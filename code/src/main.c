#include "main.h"

#include "task.h"

#define ku_THROTTLE_COMMAND_SIZE    16U
#define ku_THUSTER_NUMBER           8U

UART_HandleTypeDef      x_uart_command_handle;
SemaphoreHandle_t       x_semaphore_command_handle;

static void v_task_command_receiver( void *pv_parameters );
static void v_task_command_parser( void *pv_parameters );

static void v_system_init( void );
static void v_led_init( void );
static void v_system_clock_config( void );
static void v_error_handler( void );

static SemaphoreHandle_t    x_semaphore_throttle_command_handle;
static uint8_t              au_throttle_command[ku_THROTTLE_COMMAND_SIZE];
static uint16_t             aus_throttle[ku_THUSTER_NUMBER];

int main( void )
{
    v_system_init();

    x_semaphore_command_handle = xSemaphoreCreateBinary();
    x_semaphore_throttle_command_handle = xSemaphoreCreateBinary();

    if( x_semaphore_command_handle == NULL || x_semaphore_command_handle == NULL )
    {
        v_error_handler();
    }

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

    if( xTaskCreate( v_task_command_receiver, "command_receiver_task", 250U, NULL, 1U, NULL ) != pdPASS )
    {
        v_error_handler();
    }
    if( xTaskCreate( v_task_command_parser, "command_parser_task", 250U, NULL, 1U, NULL ) != pdPASS )
    {
        v_error_handler();
    }

    vTaskStartScheduler();

    //the program should never reach this point
    v_error_handler();

    return 0;
}

static void v_task_command_receiver( void *pv_parameters )
{
    static uint8_t u_command;

    for(;;)
    {
        if( HAL_UART_Receive_DMA( &x_uart_command_handle, &u_command, 1U ) != HAL_OK )
        {
            v_error_handler();
        }

        xSemaphoreTake( x_semaphore_command_handle, portMAX_DELAY );

        if( u_command == 0x01U )
        {
            if( HAL_UART_Receive_DMA( &x_uart_command_handle, au_throttle_command, ku_THROTTLE_COMMAND_SIZE ) != HAL_OK )
            {
                v_error_handler();
            }

            xSemaphoreTake( x_semaphore_command_handle, portMAX_DELAY );

            if ( xSemaphoreGive( x_semaphore_throttle_command_handle ) != pdTRUE )
            {
                v_error_handler();
            }
        }
    }
}

static void v_task_command_parser( void *pv_parameters )
{
    static uint8_t i;

    for(;;)
    {
        xSemaphoreTake( x_semaphore_throttle_command_handle, portMAX_DELAY );
        
        for( i = 0U ; i < ku_THROTTLE_COMMAND_SIZE ; i = i + 2 )
        {
            aus_throttle[i / 2U] = ( uint16_t )( au_throttle_command[i] | ( au_throttle_command[i + 1] << 8U ) );
        }

        HAL_GPIO_TogglePin( GPIOA, GPIO_PIN_5 );
    }
}

static void v_system_init( void )
{
    if( HAL_Init() != HAL_OK )
    {
        v_error_handler();
    }

    HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_4 );

    v_system_clock_config();

    v_led_init();
}

static void v_led_init( void )
{
    GPIO_InitTypeDef x_gpio_init_struct;

    __HAL_RCC_GPIOA_CLK_ENABLE();

    x_gpio_init_struct.Pin =        GPIO_PIN_5;
    x_gpio_init_struct.Mode =       GPIO_MODE_OUTPUT_PP;
    x_gpio_init_struct.Pull =       GPIO_PULLUP;
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

static void v_error_handler( void )
{
    for(;;)
    {
    }
}
