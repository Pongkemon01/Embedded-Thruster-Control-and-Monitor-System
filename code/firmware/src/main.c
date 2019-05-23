#include "main.h"

#include <string.h>

#include "task.h"

#include "init.h"
#include "task_command.h"
#include "task_telemetry.h"

TIM_HandleTypeDef   x_tim3_handle,
                    x_tim4_handle,
                    x_tim8_handle,
                    x_tim16_handle;
SemaphoreHandle_t   x_semaphore_pulse_handle,
                    x_semaphore_tim8_ch1_pulse_complete_handle,
                    x_semaphore_tim8_ch2_pulse_complete_handle,
                    x_semaphore_tim3_ch3_pulse_complete_handle,
                    x_semaphore_tim8_ch4_pulse_complete_handle,
                    x_semaphore_tim4_ch1_pulse_complete_handle,
                    x_semaphore_tim4_ch2_pulse_complete_handle,
                    x_semaphore_tim16_ch1_pulse_complete_handle,
                    x_semaphore_tim8_ch3_pulse_complete_handle;

extern void v_task_command_receiver( void *pv_parameters );
extern void v_task_command_parser( void *pv_parameters );
extern void v_task_telemetry_handler( void *pv_parameters );

extern void v_system_init( void );
extern void v_peripheral_init( void );
extern void v_os_element_init( void );

extern SemaphoreHandle_t    x_semaphore_throttle_handle;
extern QueueHandle_t        x_queue_telemetry_channel_handler;
extern uint16_t             aus_throttle[ku_THUSTER_NUMBER];

static void v_task_make_pulse( void *pv_parameters );
static void v_task_thruster( void *pv_parameters );

inline static uint16_t us_reverse_throttle_bit( uint16_t us_throttle );
inline static uint8_t u_generate_crc( uint16_t us_pulse );

static uint8_t  au_pulse[ku_THUSTER_NUMBER][ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT],
                au_pulse_current[ku_THUSTER_NUMBER][ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT];

int main( void )
{
    v_system_init();
    v_peripheral_init();
    v_os_element_init();
    
    if( xTaskCreate( v_task_command_receiver, "command_receiver_task", 250U, NULL, 5U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_command_parser, "command_parser_task", 250U, NULL, 3U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_make_pulse, "make_pulse_task", 250U, NULL, 4U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_thruster, "thruser_task", 250U, NULL, 6U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_telemetry_handler, "telemetry_handler_task", 250U, NULL, 2U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_telemetry_trasmitter, "telemetry_transmitter_task", 250U, NULL, 1U, NULL ) != pdPASS )
    {
        v_error_handler();
    }

    vTaskStartScheduler();

    //the program should never reach this point
    v_error_handler();

    return 0;
}

static void v_task_make_pulse( void *pv_parameters )
{
    static TickType_t   x_last_wake_time;
    static uint16_t     aus_packet_dshot[ku_THUSTER_NUMBER];
    static uint8_t      u_telemetry_channel;

    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
        xSemaphoreTake( x_semaphore_throttle_handle, portMAX_DELAY );

        xQueueReceive( x_queue_telemetry_channel_handler, &u_telemetry_channel, 0U );

        for( uint8_t i = 0U ; i < ku_THUSTER_NUMBER ; i++ )
        {
            aus_packet_dshot[i] = us_reverse_throttle_bit( aus_throttle[i] );

            if( i == u_telemetry_channel )
            {
                aus_packet_dshot[i] |= 1U << 11U ;
                u_telemetry_channel = 0xFFU;
            }

            aus_packet_dshot[i] |= (uint16_t)( u_generate_crc( aus_packet_dshot[i] ) << 12U );
        }

        if( xSemaphoreGive( x_semaphore_throttle_handle ) != pdTRUE )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_pulse_handle, portMAX_DELAY );

        for( uint8_t i = 0U ; i < ku_THUSTER_NUMBER ; i++ )
        {
            for( uint8_t j = 0U ; j < ku_DSHOT_COMMAND_SIZE_IN_BIT ; j++ )
            {
                if( ( aus_packet_dshot[i] & ( 1U << j ) ) == 0U )
                {
                    au_pulse[i][j] = 3U;
                }
                else
                {
                    au_pulse[i][j] = 6U;
                }
            }
            
            au_pulse[i][ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT - 1U] = 0U;
        }

        if( xSemaphoreGive( x_semaphore_pulse_handle ) != pdTRUE )
        {
            v_error_handler();
        }

        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( ku_TASK_SLEEP_TIME ) );
    }
}

static void v_task_thruster( void *pv_parameters )
{
    static TickType_t x_last_wake_time;

    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
        xSemaphoreTake( x_semaphore_pulse_handle, portMAX_DELAY );
        
        memcpy( ( void * ) au_pulse_current, ( void * ) au_pulse, ku_THUSTER_NUMBER * ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT );

        if( xSemaphoreGive( x_semaphore_pulse_handle ) != pdTRUE )
        {
            v_error_handler();
        }

        if( HAL_TIM_PWM_Start_DMA( &x_tim8_handle, TIM_CHANNEL_1, ( uint32_t * )au_pulse_current[0U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }
        x_tim8_handle.State = HAL_TIM_STATE_READY; // override HAL internal locking mechanism
        if( HAL_TIM_PWM_Start_DMA( &x_tim8_handle, TIM_CHANNEL_2, ( uint32_t * )au_pulse_current[1U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }
        x_tim8_handle.State = HAL_TIM_STATE_READY; // override HAL internal locking mechanism
        if( HAL_TIM_PWM_Start_DMA( &x_tim3_handle, TIM_CHANNEL_3, ( uint32_t * )au_pulse_current[2U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Start_DMA( &x_tim8_handle, TIM_CHANNEL_4, ( uint32_t * )au_pulse_current[3U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }
        x_tim8_handle.State = HAL_TIM_STATE_READY; // override HAL internal locking mechanism
        if( HAL_TIM_PWM_Start_DMA( &x_tim4_handle, TIM_CHANNEL_1, ( uint32_t * )au_pulse_current[4U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }
        x_tim4_handle.State = HAL_TIM_STATE_READY; // override HAL internal locking mechanism
        if( HAL_TIM_PWM_Start_DMA( &x_tim4_handle, TIM_CHANNEL_2, ( uint32_t * )au_pulse_current[5U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Start_DMA( &x_tim16_handle, TIM_CHANNEL_1, ( uint32_t * )au_pulse_current[6U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Start_DMA( &x_tim8_handle, TIM_CHANNEL_3, ( uint32_t * )au_pulse_current[7U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT ) != HAL_OK )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_tim8_ch1_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim8_ch2_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim3_ch3_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim8_ch4_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim4_ch1_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim4_ch2_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim16_ch1_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim8_ch3_pulse_complete_handle, portMAX_DELAY );

        if( HAL_TIM_PWM_Stop_DMA( &x_tim8_handle, TIM_CHANNEL_1 ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Stop_DMA( &x_tim8_handle, TIM_CHANNEL_2 ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Stop_DMA( &x_tim3_handle, TIM_CHANNEL_3 ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Stop_DMA( &x_tim8_handle, TIM_CHANNEL_4 ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Stop_DMA( &x_tim4_handle, TIM_CHANNEL_1 ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Stop_DMA( &x_tim4_handle, TIM_CHANNEL_2 ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Stop_DMA( &x_tim16_handle, TIM_CHANNEL_1 ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Stop_DMA( &x_tim8_handle, TIM_CHANNEL_3 ) != HAL_OK )
        {
            v_error_handler();
        }
        
        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( ku_TASK_THRUSTER_SLEEP_TIME ) );
    }
}

inline static uint16_t us_reverse_throttle_bit( uint16_t us_throttle )
{
    uint16_t reversed_throttle = 0U;

    for( uint8_t i = 0U ; i < 11U ; i++ )
    {
        reversed_throttle |= ( us_throttle & 1U ) << ( 10U - i );
        us_throttle = us_throttle >> 1U;
    }

    return reversed_throttle;
}

inline static uint8_t u_generate_crc( uint16_t us_pulse )
{
    uint8_t u_crc = 0U;

    for( uint8_t i = 0U ; i < 3U ; i++ )
    {
        u_crc ^= us_pulse & 0x000FU;

        us_pulse = us_pulse >> 4U;
    }

    return u_crc;
}
