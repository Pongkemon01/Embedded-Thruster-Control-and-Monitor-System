#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

void SystemClock_Config(void);
static void Error_Handler(void);

void vTestTask( void *pvParameters );

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    HAL_Init();
    HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_3 );

    SystemClock_Config();

    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

    GPIO_InitStruct.Pin = GPIO_PIN_5;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    if( xTaskCreate( vTestTask, "TestTask", 250, NULL, 1, NULL ) != pdPASS )
    {
        Error_Handler();
    }

    vTaskStartScheduler();

    while(1)
    {
    }
}

void vTestTask( void *pvParameters )
{
    TickType_t xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();

    while( 1 )
    {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        vTaskDelayUntil( &xLastWakeTime, pdMS_TO_TICKS( 1000U ) );
    }
}

void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_NONE;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV2;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

    if(HAL_RCC_OscConfig(&RCC_OscInitStruct) !=  HAL_OK)
    {
        Error_Handler();
    }

    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        Error_Handler();
    }
}

static void Error_Handler(void)
{
    while(1)
    {
    }
}
