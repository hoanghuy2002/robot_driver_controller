#ifndef _CORTEXM3_IRQ_H_
#define _CORTEXM3_IRQ_H_
#include <stdint.h>
#include "cortexm3.h"


void Disable_IRQ(void);
void Enable_IRQ(void);
void NVIC_Enable_IRQ(uint8_t IRQ_Number);
void NVIC_Disable_IRQ(uint8_t IRQ_Number);
void NVIC_Disable_IRQ(uint8_t IRQ_Number);
void NVIC_SetPending_IRQ(uint8_t IRQ_Number);
void NVIC_SetPriority_IRQ(uint8_t IRQ_Number, uint8_t IRQ_Priority);
void SystemPending_PENSV(void);



#endif

