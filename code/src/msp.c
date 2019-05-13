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

    HAL_NVIC_SetPriority( DMA1_Channel6_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ( DMA1_Channel6_IRQn );
}

void HAL_TIM_PWM_MspInit( TIM_HandleTypeDef *px_tim_handle )
{
    GPIO_InitTypeDef x_gpio_init_struct;

    if( px_tim_handle->Instance == TIM3 )
    {
        static DMA_HandleTypeDef x_dma_handle;

        __HAL_RCC_TIM3_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();

        x_gpio_init_struct.Pin =        GPIO_PIN_8;
        x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
        x_gpio_init_struct.Pull =       GPIO_PULLDOWN;
        x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
        x_gpio_init_struct.Alternate =  GPIO_AF2_TIM3;

        HAL_GPIO_Init( GPIOC, &x_gpio_init_struct );

        x_dma_handle.Instance =                     DMA1_Channel2;
        x_dma_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma_handle.Init.Mode =                    DMA_NORMAL;
        x_dma_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC3], x_dma_handle );

        HAL_NVIC_SetPriority( DMA1_Channel2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA1_Channel2_IRQn );
    }
    else if( px_tim_handle->Instance == TIM4 )
    {
        static DMA_HandleTypeDef    x_dma1_ch1_handle,
                                    x_dma1_ch4_handle;

        __HAL_RCC_TIM4_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();

        x_gpio_init_struct.Pin =        GPIO_PIN_6 | GPIO_PIN_7;
        x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
        x_gpio_init_struct.Pull =       GPIO_PULLDOWN;
        x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
        x_gpio_init_struct.Alternate =  GPIO_AF2_TIM4;

        HAL_GPIO_Init( GPIOB, &x_gpio_init_struct );

        x_dma1_ch1_handle.Instance =                     DMA1_Channel1;
        x_dma1_ch1_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma1_ch1_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma1_ch1_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma1_ch1_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma1_ch1_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma1_ch1_handle.Init.Mode =                    DMA_NORMAL;
        x_dma1_ch1_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma1_ch1_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma1_ch1_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC1], x_dma1_ch1_handle );

        HAL_NVIC_SetPriority( DMA1_Channel1_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA1_Channel1_IRQn );

        x_dma1_ch4_handle.Instance =                     DMA1_Channel4;
        x_dma1_ch4_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma1_ch4_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma1_ch4_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma1_ch4_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma1_ch4_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma1_ch4_handle.Init.Mode =                    DMA_NORMAL;
        x_dma1_ch4_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma1_ch4_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma1_ch4_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC2], x_dma1_ch4_handle );

        HAL_NVIC_SetPriority( DMA1_Channel4_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA1_Channel4_IRQn );
    }
}
