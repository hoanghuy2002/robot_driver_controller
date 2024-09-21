#ifndef _SYSTICK_DRIVER_H_
#define _SYSTICK_DRIVER_H_

#include "stdint.h"

void SystickTimer_Init(uint32_t SystemClock_Value);
void SystickTimer_DeInit(void);
void SysTick_DelayMs(uint32_t MiliSecond);
void SysTick_DelayUs(uint32_t MicroSecond);
void SystickIRQ_Ms(uint32_t MiliSecond);
void SystickIRQ_Us(uint32_t MicroSecond);
void SysTick_Handler(void);
#endif
