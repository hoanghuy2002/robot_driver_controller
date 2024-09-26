#ifndef _SYSTICK_DRIVER_H_
#define _SYSTICK_DRIVER_H_

#include <stdint.h>
#include "stm32f103.h"

#define Systick_Enable()    (SYSTICK->ControlStatus_Register |= 0x01)
#define Systick_Disable()   (SYSTICK->ControlStatus_Register &= ~(uint32_t)0x01)

void SystickTimer_Init(uint32_t SystemClock_Value);
void SystickTimer_DeInit(void);
void SysTick_DelayMs(uint32_t MiliSecond);
void SysTick_DelayUs(uint32_t MicroSecond);
void Setup_SystickIRQ_Ms(uint32_t MiliSecond);
void Setup_SystickIRQ_Us(uint32_t MicroSecond);
void SysTick_Handler(void);
#endif
