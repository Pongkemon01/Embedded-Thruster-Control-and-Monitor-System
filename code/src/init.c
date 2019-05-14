#include "init.h"

#include "main.h"
#include "task_command.h"
#include "task_telemetry.h"

extern UART_HandleTypeDef   x_uart_command_handle,
                            x_uart_telemetry_handler;
extern TIM_HandleTypeDef    x_tim3_handle,
                            x_tim4_handle,
                            x_tim8_handle,
                            x_tim16_handle;

static void v_uart_init( void );
static void v_timer_init( void );
static void v_gpio_telemetry_selector_init( void );
static void v_system_clock_config( void );

void v_system_init( void )
{
    if( HAL_Init() != HAL_OK )
    {
        v_error_handler();
    }

    HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_4 );

    v_system_clock_config();

    v_uart_init();
    v_timer_init();
    v_gpio_telemetry_selector_init();
}

static void v_uart_init( void )
{
    x_uart_command_handle.Instance =                        USART2;
    x_uart_command_handle.Init.BaudRate =                   9600U;
    x_uart_command_handle.Init.WordLength =                 UART_WORDLENGTH_8B;
    x_uart_command_handle.Init.StopBits =                   UART_STOPBITS_1;
    x_uart_command_handle.Init.Parity =                     UART_PARITY_NONE;
    x_uart_command_handle.Init.Mode =                       UART_MODE_TX_RX;
    x_uart_command_handle.Init.HwFlowCtl =                  UART_HWCONTROL_NONE;
    x_uart_command_handle.Init.OverSampling =               UART_OVERSAMPLING_16;
    x_uart_command_handle.Init.OneBitSampling =             UART_ONE_BIT_SAMPLE_DISABLE;
    x_uart_command_handle.AdvancedInit.AdvFeatureInit =     UART_ADVFEATURE_NO_INIT;

    if( HAL_UART_DeInit( &x_uart_command_handle ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_UART_Init( &x_uart_command_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    x_uart_telemetry_handler.Instance =                        USART1;
    x_uart_telemetry_handler.Init.BaudRate =                   115200U;
    x_uart_telemetry_handler.Init.WordLength =                 UART_WORDLENGTH_8B;
    x_uart_telemetry_handler.Init.StopBits =                   UART_STOPBITS_1;
    x_uart_telemetry_handler.Init.Parity =                     UART_PARITY_NONE;
    x_uart_telemetry_handler.Init.Mode =                       UART_MODE_RX;
    x_uart_telemetry_handler.Init.HwFlowCtl =                  UART_HWCONTROL_NONE;
    x_uart_telemetry_handler.Init.OverSampling =               UART_OVERSAMPLING_16;
    x_uart_telemetry_handler.Init.OneBitSampling =             UART_ONE_BIT_SAMPLE_DISABLE;
    x_uart_telemetry_handler.AdvancedInit.AdvFeatureInit =     UART_ADVFEATURE_NO_INIT;

    if( HAL_UART_DeInit( &x_uart_telemetry_handler ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_UART_Init( &x_uart_telemetry_handler ) != HAL_OK )
    {
        v_error_handler();
    }
}

static void v_timer_init( void )
{
    TIM_OC_InitTypeDef x_tim_channel_config_struct;

    x_tim3_handle.Instance = TIM3;
    x_tim3_handle.Init.Prescaler = ( ( uint32_t ) ( ( HAL_RCC_GetPCLK1Freq() * 2U ) / ( 150000U * 8U ) ) ) - 1U;
    x_tim3_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    x_tim3_handle.Init.Period = 8U - 1U;
    x_tim3_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    x_tim3_handle.Init.RepetitionCounter = 0U;
    x_tim3_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if( HAL_TIM_PWM_DeInit( &x_tim3_handle ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_Init( &x_tim3_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    x_tim4_handle.Instance = TIM4;
    x_tim4_handle.Init.Prescaler = ( ( uint32_t ) ( ( HAL_RCC_GetPCLK1Freq() * 2U ) / ( 150000U * 8U ) ) ) - 1U;
    x_tim4_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    x_tim4_handle.Init.Period = 8U - 1U;
    x_tim4_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    x_tim4_handle.Init.RepetitionCounter = 0U;
    x_tim4_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if( HAL_TIM_PWM_DeInit( &x_tim4_handle ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_Init( &x_tim4_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    x_tim8_handle.Instance = TIM8;
    x_tim8_handle.Init.Prescaler = ( ( uint32_t ) ( HAL_RCC_GetPCLK2Freq() / ( 150000U * 8U ) ) ) - 1U;
    x_tim8_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    x_tim8_handle.Init.Period = 8U - 1U;
    x_tim8_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    x_tim8_handle.Init.RepetitionCounter = 0U;
    x_tim8_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if( HAL_TIM_PWM_DeInit( &x_tim8_handle ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_Init( &x_tim8_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    x_tim16_handle.Instance = TIM16;
    x_tim16_handle.Init.Prescaler = ( ( uint32_t ) ( HAL_RCC_GetPCLK2Freq() / ( 150000U * 8U ) ) ) - 1U;
    x_tim16_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    x_tim16_handle.Init.Period = 8U - 1U;
    x_tim16_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    x_tim16_handle.Init.RepetitionCounter = 0U;
    x_tim16_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if( HAL_TIM_PWM_DeInit( &x_tim16_handle ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_Init( &x_tim16_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    x_tim_channel_config_struct.OCMode =        TIM_OCMODE_PWM1;
    x_tim_channel_config_struct.Pulse =         0U;
    x_tim_channel_config_struct.OCPolarity =    TIM_OCPOLARITY_HIGH;
    x_tim_channel_config_struct.OCNPolarity =   TIM_OCNPOLARITY_HIGH;
    x_tim_channel_config_struct.OCFastMode =    TIM_OCFAST_DISABLE;
    x_tim_channel_config_struct.OCIdleState =   TIM_OCIDLESTATE_RESET;
    x_tim_channel_config_struct.OCNIdleState =  TIM_OCNIDLESTATE_RESET;

    if( HAL_TIM_PWM_ConfigChannel( &x_tim8_handle, &x_tim_channel_config_struct, TIM_CHANNEL_1 ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_ConfigChannel( &x_tim8_handle, &x_tim_channel_config_struct, TIM_CHANNEL_2 ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_ConfigChannel( &x_tim3_handle, &x_tim_channel_config_struct, TIM_CHANNEL_3 ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_ConfigChannel( &x_tim8_handle, &x_tim_channel_config_struct, TIM_CHANNEL_4 ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_ConfigChannel( &x_tim4_handle, &x_tim_channel_config_struct, TIM_CHANNEL_1 ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_ConfigChannel( &x_tim4_handle, &x_tim_channel_config_struct, TIM_CHANNEL_2 ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_ConfigChannel( &x_tim16_handle, &x_tim_channel_config_struct, TIM_CHANNEL_1 ) != HAL_OK )
    {
        v_error_handler();
    }
    if( HAL_TIM_PWM_ConfigChannel( &x_tim8_handle, &x_tim_channel_config_struct, TIM_CHANNEL_3 ) != HAL_OK )
    {
        v_error_handler();
    }

}

static void v_gpio_telemetry_selector_init( void )
{
    GPIO_InitTypeDef x_gpio_init_struct;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    x_gpio_init_struct.Pin =        GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6;
    x_gpio_init_struct.Mode =       GPIO_MODE_OUTPUT_PP;
    x_gpio_init_struct.Pull =       GPIO_PULLDOWN;
    x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init( GPIOA, &x_gpio_init_struct );
}

static void v_system_clock_config( void )
{
    RCC_OscInitTypeDef      x_osc_init_struct;
    RCC_ClkInitTypeDef      x_clk_init_struct;

    x_osc_init_struct.OscillatorType =          RCC_OSCILLATORTYPE_NONE;
    x_osc_init_struct.PLL.PLLState =            RCC_PLL_ON;
    x_osc_init_struct.PLL.PLLSource =           RCC_PLLSOURCE_HSI;
    x_osc_init_struct.PLL.PREDIV =              RCC_PREDIV_DIV1;
    x_osc_init_struct.PLL.PLLMUL =              RCC_PLL_MUL9;

    if( HAL_RCC_OscConfig( &x_osc_init_struct ) !=  HAL_OK )
    {
        v_error_handler();
    }

    x_clk_init_struct.ClockType =       ( RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 );
    x_clk_init_struct.SYSCLKSource =    RCC_SYSCLKSOURCE_PLLCLK;
    x_clk_init_struct.AHBCLKDivider =   RCC_SYSCLK_DIV1;
    x_clk_init_struct.APB1CLKDivider =  RCC_HCLK_DIV2;
    x_clk_init_struct.APB2CLKDivider =  RCC_HCLK_DIV1;

    if( HAL_RCC_ClockConfig( &x_clk_init_struct, FLASH_LATENCY_2 ) != HAL_OK )
    {
        v_error_handler();
    }
}
