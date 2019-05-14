#include "task_command.h"

#include "task.h"
#include "queue.h"

UART_HandleTypeDef  x_uart_telemetry_handler;
QueueHandle_t       x_queue_telemetry_channel_handler;
SemaphoreHandle_t   x_semaphore_uart_telemetry_rx_ready_handle;

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
