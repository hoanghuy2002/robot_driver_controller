#ifndef _RCC_DRIVER_H_
#define _RCC_DRIVER_H_
#include <stdint.h>
#include "stm32f103.h"


uint32_t GetAHB_Clock(void);
uint32_t GetAPB1_Clock(void);
uint32_t GetAPB2_Clock(void);
uint32_t GetUSB_Clock(void);
uint32_t GetADC_Clock(void);
uint32_t GetTimer_Clock(TIM_RegStruct *TIM);

#endif

