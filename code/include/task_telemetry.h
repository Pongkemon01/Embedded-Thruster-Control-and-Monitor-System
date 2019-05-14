#ifndef TASK_TELEMETRY_H
#define TASK_TELEMETRY_H

#include "main.h"

void v_task_telemetry_handler( void *pv_parameters );

extern UART_HandleTypeDef   x_uart_telemetry_handler;
extern QueueHandle_t        x_queue_telemetry_channel_handler;
extern SemaphoreHandle_t    x_semaphore_uart_telemetry_rx_ready_handle;

#endif
