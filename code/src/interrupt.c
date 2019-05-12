#include "main.h"

extern UART_HandleTypeDef   x_uart_command_handle;
extern TIM_HandleTypeDef    x_tim3_handle;
extern SemaphoreHandle_t    x_semaphore_uart_rx_ready_handle;
extern SemaphoreHandle_t    x_semaphore_tim3_pulse_complete_handle;

void HAL_UART_RxCpltCallback( UART_HandleTypeDef *huart )
{
    BaseType_t x_higher_priority_task_woken = pdFALSE;

    if( xSemaphoreGiveFromISR( x_semaphore_uart_rx_ready_handle, &x_higher_priority_task_woken ) != pdTRUE )
    {
        v_error_handler();
    }

    portYIELD_FROM_ISR( x_higher_priority_task_woken );
}

void HAL_TIM_PWM_PulseFinishedCallback( TIM_HandleTypeDef *htim )
{
    BaseType_t x_higher_priority_task_woken = pdFALSE;

    if( xSemaphoreGiveFromISR( x_semaphore_tim3_pulse_complete_handle, &x_higher_priority_task_woken ) != pdTRUE )
    {
        v_error_handler();
    }

    portYIELD_FROM_ISR( x_higher_priority_task_woken );
}

void DMA1_Channel2_IRQHandler( void )
{
    HAL_DMA_IRQHandler( x_tim3_handle.hdma[TIM_DMA_ID_CC3] );
}

void DMA1_Channel6_IRQHandler( void )
{
    HAL_DMA_IRQHandler( x_uart_command_handle.hdmarx );
}
