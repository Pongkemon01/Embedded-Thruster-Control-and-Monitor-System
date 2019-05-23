#ifndef DEFINITION_H
#define DEFINITION_H

#define ku_THUSTER_NUMBER                           8U
#define ku_THROTTLE_COMMAND_SIZE                    16U
#define ku_DSHOT_COMMAND_SIZE_IN_BIT                16U
#define ku_DSHOT_COMPENSTATED_COMMAND_SIZE_IN_BIT   ( ku_DSHOT_COMMAND_SIZE_IN_BIT + 1U )
#define ku_KISS_TELEMETRY_SIZE                      10U
#define ku_TELEMETRY_SIZE                           ( ku_THUSTER_NUMBER * ( ku_KISS_TELEMETRY_SIZE - 1U ) )

#define ku_COMMAND_SET_THROTTLE                     0xA1U

#define ku_TASK_SLEEP_TIME                          33U
#define ku_TASK_THRUSTER_SLEEP_TIME                 1U
#define ku_TASK_TELEMETRY_TRASMITTER_SLEEP_TIME     10U

#endif
