#include "task_command.h"

#include "task.h"
#include "queue.h"

UART_HandleTypeDef  x_uart_telemetry_handler;
QueueHandle_t       x_queue_telemetry_channel_handler;
SemaphoreHandle_t   x_semaphore_uart_telemetry_rx_ready_handle;

static void v_telementry_select( uint8_t u_telementry_channel );

void v_task_telemetry_handler( void *pv_parameters )
{
    static TickType_t   x_last_wake_time;
    static uint8_t      u_telemetry_channel_current = 0U,
                        au_telemetry[ku_KISS_TELEMETRY_SIZE];

    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
        if( xQueueSend( x_queue_telemetry_channel_handler, ( void * )&u_telemetry_channel_current, portMAX_DELAY ) != pdPASS )
        {
            v_error_handler();
        }

        v_telementry_select( u_telemetry_channel_current );

        if( HAL_UART_Receive_DMA( &x_uart_telemetry_handler, au_telemetry, ku_KISS_TELEMETRY_SIZE ) != HAL_OK )
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

        //prevent compiler optimization
        if( au_telemetry[0] != 0U )
        {
            au_telemetry[0]++;
        }

        u_telemetry_channel_current++;
        if( u_telemetry_channel_current >= ku_THUSTER_NUMBER )
        {
            u_telemetry_channel_current = 0U;
        }

        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( 33U ) );
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
