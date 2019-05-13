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
}

void v_system_clock_config( void )
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
