#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f3xx_hal.h"

#include "FreeRTOS.h"
#include "semphr.h"

extern UART_HandleTypeDef x_command_uart_handle;

extern SemaphoreHandle_t x_command_semphore;

#endif
