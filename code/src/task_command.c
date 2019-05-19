#include "task_command.h"

#include "task.h"

#include <string.h>

UART_HandleTypeDef  x_uart_command_handle;
SemaphoreHandle_t   x_semaphore_uart_command_rx_ready_handle,
                    x_semaphore_throttle_command_handle,
                    x_semaphore_throttle_handle;
uint16_t            aus_throttle[ku_THUSTER_NUMBER];

static uint8_t  au_throttle_command[ku_THROTTLE_COMMAND_SIZE];

void v_task_command_receiver( void *pv_parameters )
{
    static const uint8_t kau_COMMAND_FALLBACK_THROTTLE[ku_THROTTLE_COMMAND_SIZE] = { 0U, 0U, 0U, 0U,
                                                                                     0U, 0U, 0U, 0U,
                                                                                     0U, 0U, 0U, 0U,
                                                                                     0U, 0U, 0U, 0U };

    static uint8_t u_command;

    for(;;)
    {
        if( HAL_UART_Receive_DMA( &x_uart_command_handle, &u_command, 1U ) != HAL_OK )
        {
            v_error_handler();
        }

        if( xSemaphoreTake( x_semaphore_uart_command_rx_ready_handle, pdMS_TO_TICKS( 100U ) ) == pdPASS )
        {
            if( u_command == ku_COMMAND_SET_THROTTLE )
            {
                xSemaphoreTake( x_semaphore_throttle_command_handle, portMAX_DELAY );

                if( HAL_UART_Receive_DMA( &x_uart_command_handle, au_throttle_command, ku_THROTTLE_COMMAND_SIZE ) != HAL_OK )
                {
                    v_error_handler();
                }

                if( xSemaphoreTake( x_semaphore_uart_command_rx_ready_handle, pdMS_TO_TICKS( 120U ) ) != pdPASS )
                {
                    if( HAL_UART_DMAStop( &x_uart_command_handle ) != HAL_OK )
                    {
                        v_error_handler();
                    }
                }

                if( xSemaphoreGive( x_semaphore_throttle_command_handle ) != pdTRUE )
                {
                    v_error_handler();
                }
            }
        }
        else
        {
            if( HAL_UART_DMAStop( &x_uart_command_handle ) != HAL_OK )
            {
                v_error_handler();
            }

            xSemaphoreTake( x_semaphore_throttle_command_handle, portMAX_DELAY );

            memcpy( ( void * ) au_throttle_command, ( void * ) kau_COMMAND_FALLBACK_THROTTLE, ku_THROTTLE_COMMAND_SIZE );

            if( xSemaphoreGive( x_semaphore_throttle_command_handle ) != pdTRUE )
            {
                v_error_handler();
            }
        }
    }
}

void v_task_command_parser( void *pv_parameters )
{
    static TickType_t   x_last_wake_time;
    static uint8_t      au_copy_throttle_command[ku_THROTTLE_COMMAND_SIZE];

    x_last_wake_time = xTaskGetTickCount();

    for(;;)
    {
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

        vTaskDelayUntil( &x_last_wake_time, pdMS_TO_TICKS( ku_TASK_SLEEP_TIME ) );
    }
}
