#include "main.h"

void HAL_UART_MspInit( UART_HandleTypeDef *px_uart_handle )
{
    static DMA_HandleTypeDef    x_dma_handle;
    GPIO_InitTypeDef            x_gpio_init_struct;

    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_DMA1_CLK_ENABLE();

    x_gpio_init_struct.Pin =        GPIO_PIN_2 | GPIO_PIN_3;
    x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
    x_gpio_init_struct.Pull =       GPIO_PULLUP;
    x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
    x_gpio_init_struct.Alternate =  GPIO_AF7_USART2;

    HAL_GPIO_Init( GPIOA, &x_gpio_init_struct );

    x_dma_handle.Instance =                     DMA1_Channel6;
    x_dma_handle.Init.Direction =               DMA_PERIPH_TO_MEMORY;
    x_dma_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
    x_dma_handle.Init.MemInc =                  DMA_MINC_ENABLE;
    x_dma_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_BYTE;
    x_dma_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
    x_dma_handle.Init.Mode =                    DMA_NORMAL;
    x_dma_handle.Init.Priority =                DMA_PRIORITY_HIGH;

    if( HAL_DMA_DeInit( &x_dma_handle ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_DMA_Init( &x_dma_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    __HAL_LINKDMA( px_uart_handle, hdmarx, x_dma_handle );

    HAL_NVIC_SetPriority( DMA1_Channel6_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ( DMA1_Channel6_IRQn );
}
