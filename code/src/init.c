#include "init.h"

#include "main.h"

void v_system_init( void )
{
    if( HAL_Init() != HAL_OK )
    {
        v_error_handler();
    }

    HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_4 );

    v_system_clock_config();

    v_led_init();
}

void v_led_init( void )
{
    GPIO_InitTypeDef x_gpio_init_struct;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    x_gpio_init_struct.Pin =        GPIO_PIN_5;
    x_gpio_init_struct.Mode =       GPIO_MODE_OUTPUT_PP;
    x_gpio_init_struct.Pull =       GPIO_PULLUP;
    x_gpio_init_struct.Speed =      GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init( GPIOA, &x_gpio_init_struct );
}

void v_system_clock_config( void )
{
    RCC_OscInitTypeDef      x_osc_init_struct;
    RCC_ClkInitTypeDef      x_clk_init_struct;

    x_osc_init_struct.OscillatorType =          RCC_OSCILLATORTYPE_NONE;
    x_osc_init_struct.PLL.PLLState =            RCC_PLL_ON;
    x_osc_init_struct.PLL.PLLSource =           RCC_PLLSOURCE_HSI;
    x_osc_init_struct.PLL.PREDIV =              RCC_PREDIV_DIV2;
    x_osc_init_struct.PLL.PLLMUL =              RCC_PLL_MUL16;
    x_osc_init_struct.HSICalibrationValue =     RCC_HSICALIBRATION_DEFAULT;

    if( HAL_RCC_OscConfig( &x_osc_init_struct ) !=  HAL_OK )
    {
        v_error_handler();
    }

    x_clk_init_struct.ClockType =       (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    x_clk_init_struct.SYSCLKSource =    RCC_SYSCLKSOURCE_PLLCLK;
    x_clk_init_struct.AHBCLKDivider =   RCC_SYSCLK_DIV1;
    x_clk_init_struct.APB1CLKDivider =  RCC_HCLK_DIV2;
    x_clk_init_struct.APB2CLKDivider =  RCC_HCLK_DIV1;

    if( HAL_RCC_ClockConfig( &x_clk_init_struct, FLASH_LATENCY_2 ) != HAL_OK )
    {
        v_error_handler();
    }
}
