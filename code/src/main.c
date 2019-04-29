#include "main.h"

#include "task.h"

UART_HandleTypeDef x_command_uart_handle;

SemaphoreHandle_t x_command_semphore;

static void v_command_receiver_task( void *pv_parameters );

static void v_system_init( void );
static void v_init_led( void );
static void v_config_system_clock( void );
static void v_error_handler( void );

int main( void )
{
    v_system_init();

    x_command_semphore = xSemaphoreCreateBinary();

    if( x_command_semphore == NULL )
    {
        v_error_handler();
    }

    x_command_uart_handle.Instance = USART2;
    x_command_uart_handle.Init.BaudRate = 9600U;
    x_command_uart_handle.Init.WordLength = UART_WORDLENGTH_8B;
    x_command_uart_handle.Init.StopBits = UART_STOPBITS_1;
    x_command_uart_handle.Init.Parity = UART_PARITY_NONE;
    x_command_uart_handle.Init.Mode = UART_MODE_TX_RX;
    x_command_uart_handle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    x_command_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;
    x_command_uart_handle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;

    x_command_uart_handle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if( HAL_UART_DeInit( &x_command_uart_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    if( HAL_UART_Init( &x_command_uart_handle ) != HAL_OK )
    {
        v_error_handler();
    }

    if( xTaskCreate( v_command_receiver_task, "command_receiver_task", 250U, NULL, 1U, NULL ) != pdPASS )
    {
        v_error_handler();
    }

    vTaskStartScheduler();

    //the program should never reach this point
    v_error_handler();

    return 0;
}

static void v_command_receiver_task( void *pv_parameters )
{
    static uint8_t u_command;
    static uint8_t au_throttle_command[16U];

    for(;;)
    {
        if( HAL_UART_Receive_DMA( &x_command_uart_handle, &u_command, 1U ) != HAL_OK )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_command_semphore, portMAX_DELAY );

        if( u_command == 0x01U )
        {
            if( HAL_UART_Receive_DMA( &x_command_uart_handle, (uint8_t *)au_throttle_command, 16U ) != HAL_OK )
            {
                v_error_handler();
            }

            xSemaphoreTake( x_command_semphore, portMAX_DELAY );
            
            HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
        }
    }
}

static void v_system_init( void )
{
    if( HAL_Init() != HAL_OK )
    {
        v_error_handler();
    }

    HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_4 );

    v_config_system_clock();

    v_init_led();
}

static void v_init_led( void )
{
    GPIO_InitTypeDef x_gpio_init_struct;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    x_gpio_init_struct.Pin = GPIO_PIN_5;
    x_gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;
    x_gpio_init_struct.Pull = GPIO_PULLUP;
    x_gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init( GPIOA, &x_gpio_init_struct );
}

static void v_config_system_clock( void )
{
    RCC_OscInitTypeDef x_osc_init_struct;
    RCC_ClkInitTypeDef x_clk_init_struct;

    x_osc_init_struct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
    x_osc_init_struct.PLL.PLLState = RCC_PLL_ON;
    x_osc_init_struct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    x_osc_init_struct.PLL.PREDIV = RCC_PREDIV_DIV2;
    x_osc_init_struct.PLL.PLLMUL = RCC_PLL_MUL16;
    x_osc_init_struct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    if( HAL_RCC_OscConfig( &x_osc_init_struct ) !=  HAL_OK )
    {
        v_error_handler();
    }

    x_clk_init_struct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    x_clk_init_struct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    x_clk_init_struct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    x_clk_init_struct.APB1CLKDivider = RCC_HCLK_DIV2;
    x_clk_init_struct.APB2CLKDivider = RCC_HCLK_DIV1;

    if( HAL_RCC_ClockConfig( &x_clk_init_struct, FLASH_LATENCY_2 ) != HAL_OK )
    {
        v_error_handler();
    }
}

static void v_error_handler( void )
{
    for(;;)
    {
    }
}
