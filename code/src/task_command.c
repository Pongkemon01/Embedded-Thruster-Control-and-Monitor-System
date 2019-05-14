#include "task_command.h"

#include "task.h"

#include <string.h>

UART_HandleTypeDef  x_uart_command_handle;
SemaphoreHandle_t   x_semaphore_uart_command_rx_ready_handle,
                    x_semaphore_throttle_command_ready_handle,
                    x_semaphore_throttle_command_handle,
                    x_semaphore_throttle_handle;
uint16_t            aus_throttle[ku_THUSTER_NUMBER];

static uint8_t  au_throttle_command[ku_THROTTLE_COMMAND_SIZE];

void v_task_command_receiver( void *pv_parameters )
{
    static uint8_t u_command;

    for(;;)
    {
        if( HAL_UART_Receive_DMA( &x_uart_command_handle, &u_command, 1U ) != HAL_OK )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_uart_command_rx_ready_handle, portMAX_DELAY );

        if( u_command == 0xA1U )
        {
            xSemaphoreTake( x_semaphore_throttle_command_handle, portMAX_DELAY );

            if( HAL_UART_Receive_DMA( &x_uart_command_handle, au_throttle_command, ku_THROTTLE_COMMAND_SIZE ) != HAL_OK )
            {
                v_error_handler();
            }

            xSemaphoreTake( x_semaphore_uart_command_rx_ready_handle, portMAX_DELAY );

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

void v_task_command_parser( void *pv_parameters )
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
