#include "task_telemetry.h"

#include "task.h"
#include "queue.h"

UART_HandleTypeDef  x_uart_telemetry_handler;
QueueHandle_t       x_queue_telemetry_channel_handler;
SemaphoreHandle_t   x_semaphore_uart_telemetry_rx_ready_handle,
                    x_semaphore_uart_telemetry_tx_complete_handle,
                    x_semaphore_telemetry_handle;

extern UART_HandleTypeDef x_uart_command_handle;

static void v_telementry_select( uint8_t u_telementry_channel );
static uint8_t u_generate_crc8( uint8_t au_data[], uint8_t u_length );
static uint8_t u_update_crc8( uint8_t u_crc, uint8_t u_crc_seed );

static uint8_t au_telemetry[ku_THUSTER_NUMBER][ku_KISS_TELEMETRY_SIZE - 1];

void v_task_telemetry_handler( void *pv_parameters )
{
    static TickType_t   x_last_wake_time;
    static uint8_t      u_telemetry_channel_current = 0U,
                        au_telemetry_current[ku_KISS_TELEMETRY_SIZE];

    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
        if( xQueueSend( x_queue_telemetry_channel_handler, ( void * )&u_telemetry_channel_current, portMAX_DELAY ) != pdPASS )
        {
            v_error_handler();
        }

        v_telementry_select( u_telemetry_channel_current );

        if( HAL_UART_Receive_DMA( &x_uart_telemetry_handler, au_telemetry_current, ku_KISS_TELEMETRY_SIZE ) != HAL_OK )
        {
            v_error_handler();
        }

        if( xSemaphoreTake( x_semaphore_uart_telemetry_rx_ready_handle, pdMS_TO_TICKS( 2U ) ) != pdPASS )
        {
            if( HAL_UART_DMAStop( &x_uart_telemetry_handler ) != HAL_OK )
            {
                v_error_handler();
            }
        }
        else
        {
            if( au_telemetry_current[ku_KISS_TELEMETRY_SIZE - 1U] == u_generate_crc8( au_telemetry_current, ku_KISS_TELEMETRY_SIZE - 1 ) )
            {
                xSemaphoreTake( x_semaphore_telemetry_handle, portMAX_DELAY );

                for( uint8_t i = 0U ; i < ku_KISS_TELEMETRY_SIZE - 1 ; i++ )
                {
                    au_telemetry[u_telemetry_channel_current][i] = au_telemetry_current[i];
                }

                if( xSemaphoreGive( x_semaphore_telemetry_handle ) != pdPASS )
                {
                    v_error_handler();
                }
            }
        }

        u_telemetry_channel_current++;
        if( u_telemetry_channel_current >= ku_THUSTER_NUMBER )
        {
            u_telemetry_channel_current = 0U;
        }

        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( 33U ) );
    }
}

void v_task_telemetry_trasmitter( void *pv_parameters )
{
    static TickType_t       x_last_wake_time;
    static const uint8_t    au_telemetry_begin[] = { 0xAAU, 0xAAU, 0xAAU, 0xAAU, 
                                                     0xAAU, 0xAAU, 0xAAU, 0xAAU };
    
    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
        if( HAL_UART_Transmit_IT( &x_uart_command_handle, ( uint8_t * )au_telemetry_begin, 8U ) != HAL_OK )
        {
            v_error_handler();
        }
        xSemaphoreTake( x_semaphore_uart_telemetry_tx_complete_handle, portMAX_DELAY );

        xSemaphoreTake( x_semaphore_telemetry_handle, portMAX_DELAY );

        if( HAL_UART_Transmit_IT( &x_uart_command_handle, ( uint8_t * )au_telemetry, ku_THUSTER_NUMBER * ( ku_KISS_TELEMETRY_SIZE - 1 ) ) != HAL_OK )
        {
            v_error_handler();
        }
        
        xSemaphoreTake( x_semaphore_uart_telemetry_tx_complete_handle, portMAX_DELAY );
        if( xSemaphoreGive( x_semaphore_telemetry_handle ) != pdPASS )
        {
            v_error_handler();
        }

        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( 10U ) );
    }
}

static void v_telementry_select( uint8_t u_telementry_channel )
{
    if( ( u_telementry_channel & 1U ) == 1U )
    {
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, GPIO_PIN_SET );
    }
    else
    {
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_4, GPIO_PIN_RESET );
    }
    
    if( ( u_telementry_channel & 2U ) == 2U )
    {
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_SET );
    }
    else
    {
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_5, GPIO_PIN_RESET );
    }

    if( ( u_telementry_channel & 4U ) == 4U )
    {
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_6, GPIO_PIN_SET );
    }
    else
    {
        HAL_GPIO_WritePin( GPIOA, GPIO_PIN_6, GPIO_PIN_RESET );
    }
}

static uint8_t u_generate_crc8( uint8_t au_data[], uint8_t u_length )
{
    uint8_t crc = 0U;

    for( uint8_t i = 0U ; i < u_length ; i++ )
    {
        crc = u_update_crc8( au_data[i], crc );
    }

    return crc;
}

static uint8_t u_update_crc8( uint8_t u_crc, uint8_t u_crc_seed )
{
    uint8_t u_crc_update;
    
    u_crc_update = u_crc;
    u_crc_update ^= u_crc_seed;

    for( uint8_t i = 0U ; i < 8U ; i++ )
    {
        u_crc_update = ( u_crc_update & 0x80U ) ? 0x7U ^ ( u_crc_update << 1 ) : ( u_crc_update << 1 );
    }

    return u_crc_update;
}
