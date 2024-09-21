#include <stdint.h>

#define RTOS_Success 		1
#define RTOS_OverTask		0
#define RTOS_Failure 		-1



#define TaskTimer_Tick							 0.01				// 10ms
#define Task_TickMiliSecond					 (TaskTimer_Tick*1000)
#define Task_TickSencond						 TaskTimer_Tick
#define Task_DelayWaitEvent					 -0.16f

int8_t RTOS_Create_Task(void (*Task_Handler)(void),uint16_t Task_Size,uint8_t Task_Priority,int16_t Task_Symbol);
int8_t RTOS_Delete_Task(uint16_t Task_Symbol);
void RTOS_Run_Task(void);
void RTOS_Delay_Task(float Time_Delay);


