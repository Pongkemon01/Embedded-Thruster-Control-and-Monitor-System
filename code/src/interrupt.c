#include "main.h"

extern UART_HandleTypeDef x_command_uart_handle;

extern SemaphoreHandle_t x_command_semphore;

void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart )
{
    BaseType_t x_higher_priority_task_woken = pdFALSE;

    xSemaphoreGiveFromISR( x_command_semphore, &x_higher_priority_task_woken );

    portYIELD_FROM_ISR( x_higher_priority_task_woken );
}

void DMA1_Channel6_IRQHandler( void )
{
    HAL_DMA_IRQHandler( x_command_uart_handle.hdmarx );
}
