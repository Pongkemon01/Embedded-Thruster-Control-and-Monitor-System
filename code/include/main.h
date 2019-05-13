#ifndef MAIN_H
#define MAIN_H

#include "stm32f3xx_hal.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "error_handler.h"

#define ku_THUSTER_NUMBER                   8U
#define ku_THROTTLE_COMMAND_SIZE            16U
#define ku_DSHOT_COMMAND_SIZE               16U
#define ku_DSHOT_COMPENSTATED_COMMAND_SIZE  (ku_DSHOT_COMMAND_SIZE + 1U)

extern UART_HandleTypeDef   x_uart_command_handle;
extern TIM_HandleTypeDef    x_tim3_handle;
extern TIM_HandleTypeDef    x_tim4_handle;
extern SemaphoreHandle_t    x_semaphore_uart_rx_ready_handle;
extern SemaphoreHandle_t    x_semaphore_tim3_pulse_complete_handle;
extern SemaphoreHandle_t    x_semaphore_tim4_ch1_pulse_complete_handle;
extern SemaphoreHandle_t    x_semaphore_tim4_ch2_pulse_complete_handle;

#endif
