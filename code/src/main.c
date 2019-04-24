#include "main.h"

#include "FreeRTOS.h"
#include "task.h"

static void vConfigSystemClock( void );
static void vError_Handler( void );

static void vTestTask( void *pvParameters );

int main( void )
{
    if( HAL_Init() != HAL_OK )
    {
        vError_Handler();
    }

    HAL_NVIC_SetPriorityGrouping( NVIC_PRIORITYGROUP_3 );

    vConfigSystemClock();

    if( xTaskCreate( vTestTask, "test_task", 250U, NULL, 1U, NULL ) != pdPASS )
    {
        vError_Handler();
    }

    vTaskStartScheduler();

    //the program should never reach this point
    vError_Handler();

    return 0;
}

static void vTestTask( void *pvParameters )
{
    for(;;)
    {
    }
}

static void vConfigSystemClock(void)
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
        vError_Handler();
    }

    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if(HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
        vError_Handler();
    }
}

static void vError_Handler( void )
{
    for(;;)
    {
    }
}
