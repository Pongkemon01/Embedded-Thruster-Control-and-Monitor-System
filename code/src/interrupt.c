#include "main.h"

extern UART_HandleTypeDef   x_uart_command_handle;
extern SemaphoreHandle_t    x_semaphore_command_handle;

void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart )
{
    BaseType_t x_higher_priority_task_woken = pdFALSE;

    if( xSemaphoreGiveFromISR( x_semaphore_command_handle, &x_higher_priority_task_woken ) != pdTRUE )
    {
        for(;;)
        {
        }
    }

    portYIELD_FROM_ISR( x_higher_priority_task_woken );
}

void DMA1_Channel6_IRQHandler( void )
{
    HAL_DMA_IRQHandler( x_uart_command_handle.hdmarx );
}
