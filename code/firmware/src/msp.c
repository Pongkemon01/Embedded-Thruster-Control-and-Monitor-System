#include "main.h"

void HAL_UART_MspInit( UART_HandleTypeDef *px_uart_handle )
{
    GPIO_InitTypeDef x_gpio_init_struct;

    if( px_uart_handle->Instance == USART1 )
    {
        static DMA_HandleTypeDef x_dma1_ch5_handle;

        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();

        x_gpio_init_struct.Pin =        GPIO_PIN_9 | GPIO_PIN_10;
        x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
        x_gpio_init_struct.Pull =       GPIO_PULLUP;
        x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
        x_gpio_init_struct.Alternate =  GPIO_AF7_USART1;

        HAL_GPIO_Init( GPIOA, &x_gpio_init_struct );

        x_dma1_ch5_handle.Instance =                     DMA1_Channel5;
        x_dma1_ch5_handle.Init.Direction =               DMA_PERIPH_TO_MEMORY;
        x_dma1_ch5_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma1_ch5_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma1_ch5_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_BYTE;
        x_dma1_ch5_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma1_ch5_handle.Init.Mode =                    DMA_NORMAL;
        x_dma1_ch5_handle.Init.Priority =                DMA_PRIORITY_HIGH;

        if( HAL_DMA_DeInit( &x_dma1_ch5_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma1_ch5_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_uart_handle, hdmarx, x_dma1_ch5_handle );

        HAL_NVIC_SetPriority( DMA1_Channel5_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ( DMA1_Channel5_IRQn );

        HAL_NVIC_SetPriority( USART1_IRQn, 8, 0);
        HAL_NVIC_EnableIRQ( USART1_IRQn );
    }
    else if( px_uart_handle->Instance == USART2 )
    {
        static DMA_HandleTypeDef x_dma1_ch6_handle;

        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();

        x_gpio_init_struct.Pin =        GPIO_PIN_3;
        x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
        x_gpio_init_struct.Pull =       GPIO_PULLUP;
        x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
        x_gpio_init_struct.Alternate =  GPIO_AF7_USART2;

        HAL_GPIO_Init( GPIOA, &x_gpio_init_struct );

        x_dma1_ch6_handle.Instance =                     DMA1_Channel6;
        x_dma1_ch6_handle.Init.Direction =               DMA_PERIPH_TO_MEMORY;
        x_dma1_ch6_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma1_ch6_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma1_ch6_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_BYTE;
        x_dma1_ch6_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma1_ch6_handle.Init.Mode =                    DMA_NORMAL;
        x_dma1_ch6_handle.Init.Priority =                DMA_PRIORITY_MEDIUM;

        if( HAL_DMA_DeInit( &x_dma1_ch6_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma1_ch6_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_uart_handle, hdmarx, x_dma1_ch6_handle );

        HAL_NVIC_SetPriority( DMA1_Channel6_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ( DMA1_Channel6_IRQn );

        HAL_NVIC_SetPriority( USART2_IRQn, 7, 0);
        HAL_NVIC_EnableIRQ( USART2_IRQn );
    }
}

void HAL_TIM_PWM_MspInit( TIM_HandleTypeDef *px_tim_handle )
{
    GPIO_InitTypeDef x_gpio_init_struct;

    if( px_tim_handle->Instance == TIM3 )
    {
        static DMA_HandleTypeDef x_dma1_ch2_handle;

        __HAL_RCC_TIM3_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();

        x_gpio_init_struct.Pin =        GPIO_PIN_8;
        x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
        x_gpio_init_struct.Pull =       GPIO_PULLDOWN;
        x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
        x_gpio_init_struct.Alternate =  GPIO_AF2_TIM3;

        HAL_GPIO_Init( GPIOC, &x_gpio_init_struct );

        x_dma1_ch2_handle.Instance =                     DMA1_Channel2;
        x_dma1_ch2_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma1_ch2_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma1_ch2_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma1_ch2_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma1_ch2_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma1_ch2_handle.Init.Mode =                    DMA_NORMAL;
        x_dma1_ch2_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma1_ch2_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma1_ch2_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC3], x_dma1_ch2_handle );

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
    else if( px_tim_handle->Instance == TIM8 )
    {
        static DMA_HandleTypeDef    x_dma2_ch1_handle,
                                    x_dma2_ch2_handle,
                                    x_dma2_ch3_handle,
                                    x_dma2_ch5_handle;

        __HAL_RCC_TIM8_CLK_ENABLE();
        __HAL_RCC_GPIOC_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_DMA2_CLK_ENABLE();

        x_gpio_init_struct.Pin =        GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_9;
        x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
        x_gpio_init_struct.Pull =       GPIO_PULLDOWN;
        x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
        x_gpio_init_struct.Alternate =  GPIO_AF4_TIM8;

        HAL_GPIO_Init( GPIOC, &x_gpio_init_struct );

        x_gpio_init_struct.Pin =        GPIO_PIN_9;
        x_gpio_init_struct.Alternate =  GPIO_AF10_TIM8;

        HAL_GPIO_Init( GPIOB, &x_gpio_init_struct );

        x_dma2_ch1_handle.Instance =                     DMA2_Channel1;
        x_dma2_ch1_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma2_ch1_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma2_ch1_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma2_ch1_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma2_ch1_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma2_ch1_handle.Init.Mode =                    DMA_NORMAL;
        x_dma2_ch1_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma2_ch1_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma2_ch1_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC3], x_dma2_ch1_handle );

        HAL_NVIC_SetPriority( DMA2_Channel1_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA2_Channel1_IRQn );

        x_dma2_ch2_handle.Instance =                     DMA2_Channel2;
        x_dma2_ch2_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma2_ch2_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma2_ch2_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma2_ch2_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma2_ch2_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma2_ch2_handle.Init.Mode =                    DMA_NORMAL;
        x_dma2_ch2_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma2_ch2_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma2_ch2_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC4], x_dma2_ch2_handle );

        HAL_NVIC_SetPriority( DMA2_Channel2_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA2_Channel2_IRQn );

        x_dma2_ch3_handle.Instance =                     DMA2_Channel3;
        x_dma2_ch3_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma2_ch3_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma2_ch3_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma2_ch3_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma2_ch3_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma2_ch3_handle.Init.Mode =                    DMA_NORMAL;
        x_dma2_ch3_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma2_ch3_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma2_ch3_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC1], x_dma2_ch3_handle );

        HAL_NVIC_SetPriority( DMA2_Channel3_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA2_Channel3_IRQn );

        x_dma2_ch5_handle.Instance =                     DMA2_Channel5;
        x_dma2_ch5_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma2_ch5_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma2_ch5_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma2_ch5_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma2_ch5_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma2_ch5_handle.Init.Mode =                    DMA_NORMAL;
        x_dma2_ch5_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma2_ch5_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma2_ch5_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC2], x_dma2_ch5_handle );

        HAL_NVIC_SetPriority( DMA2_Channel5_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA2_Channel5_IRQn );
    }
    else if( px_tim_handle->Instance == TIM16 )
    {
        static DMA_HandleTypeDef    x_dma1_ch3_handle;

        __HAL_RCC_TIM16_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();

        x_gpio_init_struct.Pin =        GPIO_PIN_8;
        x_gpio_init_struct.Mode =       GPIO_MODE_AF_PP;
        x_gpio_init_struct.Pull =       GPIO_PULLDOWN;
        x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;
        x_gpio_init_struct.Alternate =  GPIO_AF1_TIM16;

        HAL_GPIO_Init( GPIOB, &x_gpio_init_struct );

        x_dma1_ch3_handle.Instance =                     DMA1_Channel3;
        x_dma1_ch3_handle.Init.Direction =               DMA_MEMORY_TO_PERIPH;
        x_dma1_ch3_handle.Init.PeriphInc =               DMA_PINC_DISABLE;
        x_dma1_ch3_handle.Init.MemInc =                  DMA_MINC_ENABLE;
        x_dma1_ch3_handle.Init.PeriphDataAlignment =     DMA_PDATAALIGN_WORD;
        x_dma1_ch3_handle.Init.MemDataAlignment =        DMA_MDATAALIGN_BYTE;
        x_dma1_ch3_handle.Init.Mode =                    DMA_NORMAL;
        x_dma1_ch3_handle.Init.Priority =                DMA_PRIORITY_VERY_HIGH;

        if( HAL_DMA_DeInit( &x_dma1_ch3_handle ) != HAL_OK )
        {
            v_error_handler();
        }
        if( HAL_DMA_Init( &x_dma1_ch3_handle ) != HAL_OK )
        {
            v_error_handler();
        }

        __HAL_LINKDMA( px_tim_handle, hdma[TIM_DMA_ID_CC1], x_dma1_ch3_handle );

        HAL_NVIC_SetPriority( DMA1_Channel3_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ( DMA1_Channel3_IRQn );
    }
}
