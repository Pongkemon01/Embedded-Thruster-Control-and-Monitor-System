#include "main.h"

#include "task.h"

#include "init.h"

#include <string.h>

UART_HandleTypeDef      x_uart_command_handle;
TIM_HandleTypeDef       x_tim3_handle,
                        x_tim4_handle;
SemaphoreHandle_t       x_semaphore_uart_rx_ready_handle,
                        x_semaphore_tim3_ch3_pulse_complete_handle,
                        x_semaphore_tim4_ch1_pulse_complete_handle,
                        x_semaphore_tim4_ch2_pulse_complete_handle;

static void v_task_command_receiver( void *pv_parameters );
static void v_task_command_parser( void *pv_parameters );
static void v_task_make_pulse( void *pv_parameters );
static void v_task_thruster( void *pv_parameters );

static uint8_t u_generate_crc( uint16_t us_pulse );

static SemaphoreHandle_t    x_semaphore_throttle_command_handle,
                            x_semaphore_throttle_command_ready_handle,
                            x_semaphore_throttle_handle,
                            x_semaphore_pulse_handle;
static uint16_t             aus_throttle[ku_THUSTER_NUMBER];
static uint8_t              au_throttle_command[ku_THROTTLE_COMMAND_SIZE],
                            au_pulse[ku_THUSTER_NUMBER][ku_DSHOT_COMPENSTATED_COMMAND_SIZE],
                            au_pulse_current[ku_THUSTER_NUMBER][ku_DSHOT_COMPENSTATED_COMMAND_SIZE];

int main( void )
{
    v_system_init();

    x_semaphore_uart_rx_ready_handle =              xSemaphoreCreateBinary();
    x_semaphore_tim3_ch3_pulse_complete_handle =    xSemaphoreCreateBinary();
    x_semaphore_tim4_ch1_pulse_complete_handle =    xSemaphoreCreateBinary();
    x_semaphore_tim4_ch2_pulse_complete_handle =    xSemaphoreCreateBinary();
    x_semaphore_throttle_command_ready_handle =     xSemaphoreCreateBinary();
    x_semaphore_throttle_command_handle =           xSemaphoreCreateMutex();
    x_semaphore_throttle_handle =                   xSemaphoreCreateMutex();
    x_semaphore_pulse_handle =                      xSemaphoreCreateMutex();

    if( x_semaphore_uart_rx_ready_handle == NULL ||
        x_semaphore_tim3_ch3_pulse_complete_handle == NULL ||
        x_semaphore_tim4_ch1_pulse_complete_handle == NULL ||
        x_semaphore_tim4_ch2_pulse_complete_handle == NULL ||
        x_semaphore_throttle_command_ready_handle == NULL ||
        x_semaphore_throttle_command_handle == NULL ||
        x_semaphore_throttle_handle == NULL ||
        x_semaphore_pulse_handle == NULL )
    {
        v_error_handler();
    }
    
    if( xTaskCreate( v_task_command_receiver, "command_receiver_task", 250U, NULL, 3U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_command_parser, "command_parser_task", 250U, NULL, 1U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_make_pulse, "make_pulse_task", 250U, NULL, 2U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_thruster, "thruser_task", 250U, NULL, 4U, NULL ) != pdPASS )
    {
        v_error_handler();
    }

    vTaskStartScheduler();

    //the program should never reach this point
    v_error_handler();

    return 0;
}

static void v_task_command_receiver( void *pv_parameters )
{
    static uint8_t u_command;

    for(;;)
    {
        if( HAL_UART_Receive_DMA( &x_uart_command_handle, &u_command, 1U ) != HAL_OK )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_uart_rx_ready_handle, portMAX_DELAY );

        if( u_command == 0x01U )
        {
            xSemaphoreTake( x_semaphore_throttle_command_handle, portMAX_DELAY );

            if( HAL_UART_Receive_DMA( &x_uart_command_handle, au_throttle_command, ku_THROTTLE_COMMAND_SIZE ) != HAL_OK )
            {
                v_error_handler();
            }

            xSemaphoreTake( x_semaphore_uart_rx_ready_handle, portMAX_DELAY );

            if( xSemaphoreGive( x_semaphore_throttle_command_ready_handle ) != pdTRUE )
            {
                v_error_handler();
            }
            if( xSemaphoreGive( x_semaphore_throttle_command_handle ) != pdTRUE )
            {
                v_error_handler();
            }
        }
    }
}

static void v_task_command_parser( void *pv_parameters )
{
    static uint8_t au_copy_throttle_command[ku_THROTTLE_COMMAND_SIZE];

    for(;;)
    {
        xSemaphoreTake( x_semaphore_throttle_command_ready_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_throttle_command_handle, portMAX_DELAY );

        memcpy( ( void * )au_copy_throttle_command, ( void * )au_throttle_command, ku_THROTTLE_COMMAND_SIZE );

        if( xSemaphoreGive( x_semaphore_throttle_command_handle ) != pdTRUE )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_throttle_handle, portMAX_DELAY );
        
        for( uint8_t i = 0U ; i < ku_THROTTLE_COMMAND_SIZE ; i = i + 2U )
        {
            aus_throttle[i / 2U] = ( uint16_t )( au_copy_throttle_command[i] | ( au_copy_throttle_command[i + 1U] << 8U ) );
        }

        if( xSemaphoreGive( x_semaphore_throttle_handle ) != pdTRUE )
        {
            v_error_handler();
        }
    }
}

static void v_task_make_pulse( void *pv_parameters )
{
    static TickType_t   x_last_wake_time;
    static uint16_t     aus_packet_dshot[ku_THUSTER_NUMBER];

    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
        xSemaphoreTake( x_semaphore_throttle_handle, portMAX_DELAY );

        for( uint8_t i = 0U ; i < ku_THUSTER_NUMBER ; i++ )
        {
            //TODO: add telemetry bit
            aus_packet_dshot[i] = aus_throttle[i];

            aus_packet_dshot[i] |= (uint16_t)( u_generate_crc( aus_packet_dshot[i] ) << 12U );
        }

        if( xSemaphoreGive( x_semaphore_throttle_handle ) != pdTRUE )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_pulse_handle, portMAX_DELAY );

        for( uint8_t i = 0U ; i < ku_THUSTER_NUMBER ; i++ )
        {
            for( uint8_t j = 0U ; j < ku_DSHOT_COMMAND_SIZE ; j++ )
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
            
            au_pulse[i][ku_DSHOT_COMPENSTATED_COMMAND_SIZE - 1U ] = 0U;
        }

        if( xSemaphoreGive( x_semaphore_pulse_handle ) != pdTRUE )
        {
            v_error_handler();
        }

        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( 33U ) );
    }
}

static void v_task_thruster( void *pv_parameters )
{
    static TickType_t x_last_wake_time;

    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
        xSemaphoreTake( x_semaphore_pulse_handle, portMAX_DELAY );
        
        memcpy( ( void * ) au_pulse_current, ( void * ) au_pulse, ku_THUSTER_NUMBER * ku_DSHOT_COMPENSTATED_COMMAND_SIZE );

        if( xSemaphoreGive( x_semaphore_pulse_handle ) != pdTRUE )
        {
            v_error_handler();
        }

        if( HAL_TIM_PWM_Start_DMA( &x_tim3_handle, TIM_CHANNEL_3, ( uint32_t * )au_pulse_current[2U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_TIM_PWM_Start_DMA( &x_tim4_handle, TIM_CHANNEL_1, ( uint32_t * )au_pulse_current[4U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE ) != HAL_OK )
        {
            v_error_handler();
        }
        x_tim4_handle.State = HAL_TIM_STATE_READY;
        if( HAL_TIM_PWM_Start_DMA( &x_tim4_handle, TIM_CHANNEL_2, ( uint32_t * )au_pulse_current[5U], ku_DSHOT_COMPENSTATED_COMMAND_SIZE ) != HAL_OK )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_tim3_ch3_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim4_ch1_pulse_complete_handle, portMAX_DELAY );
        xSemaphoreTake( x_semaphore_tim4_ch2_pulse_complete_handle, portMAX_DELAY );

        if( HAL_TIM_PWM_Stop_DMA( &x_tim3_handle, TIM_CHANNEL_3 ) != HAL_OK )
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
        
        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( 1U ) );
    }
}

static uint8_t u_generate_crc( uint16_t us_pulse )
{
    uint8_t u_crc = 0U;

    for( uint8_t i = 0U ; i < 3U ; i++ )
    {
        u_crc ^= us_pulse & 0x000FU;

        us_pulse = us_pulse >> 4U;
    }

    return u_crc;
}
