#include "init.h"

#include "main.h"

extern UART_HandleTypeDef x_uart_command_handle;

static void v_uart_init( void );
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
