#ifndef MAIN_H
#define MAIN_H

#include "stm32f3xx_hal.h"

#include "FreeRTOS.h"
#include "semphr.h"

#include "error_handler.h"

#define ku_THROTTLE_COMMAND_SIZE    16U
#define ku_THUSTER_NUMBER           8U

extern UART_HandleTypeDef   x_uart_command_handle;
extern SemaphoreHandle_t    x_semaphore_command_handle;

#endif
