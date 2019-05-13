#ifndef TASK_COMMAND_H
#define TASK_COMMAND_H

#include "main.h"

void v_task_command_receiver( void *pv_parameters );
void v_task_command_parser( void *pv_parameters );

extern UART_HandleTypeDef   x_uart_command_handle;
extern SemaphoreHandle_t    x_semaphore_uart_rx_ready_handle,
                            x_semaphore_throttle_command_ready_handle,
                            x_semaphore_throttle_command_handle,
                            x_semaphore_throttle_handle;
extern uint16_t             aus_throttle[];

#endif
