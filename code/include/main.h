#ifndef MAIN_H
#define MAIN_H

#include "stm32f3xx_hal.h"

#include "FreeRTOS.h"
#include "semphr.h"

extern UART_HandleTypeDef   x_uart_command_handle;
extern SemaphoreHandle_t    x_semaphore_command_handle;

#endif
