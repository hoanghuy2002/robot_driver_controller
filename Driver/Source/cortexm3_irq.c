
#include <math.h>
#include "cortexm3_irq.h"


void Disable_IRQ()
{
	//// Set bit PRIMASK
	__asm volatile ("MOV R0,#0x1"); 
	__asm volatile("MSR PRIMASK,R0");
}

void Enable_IRQ()
{
	//// Clear bit PRIMASK
	__asm volatile ("MOV R0,#0x0"); 
	__asm volatile ("MSR PRIMASK,R0");
}
	

void NVIC_Enable_IRQ(uint8_t IRQ_Number)
{
	
  NVIC->SetEnable_IRQ[IRQ_Number/32] |= (uint32_t)(1<<(IRQ_Number-(IRQ_Number/32)*32));
}

void NVIC_Disable_IRQ(uint8_t IRQ_Number)
{
    NVIC->ClearEnable_IRQ[IRQ_Number/32] |= (uint32_t)(1<<(IRQ_Number-(IRQ_Number/32)*32));
}

void NVIC_SetPending_IRQ(uint8_t IRQ_Number)
{
    NVIC->SetPending_IRQ[IRQ_Number/32] |= (uint32_t)(1<<(IRQ_Number-(IRQ_Number/32)*32));
}


void NVIC_SetPriority_IRQ(uint8_t IRQ_Number, uint8_t IRQ_Priority)
{
    if (IRQ_Priority <= 15)
    {
      NVIC->IRQPriority[IRQ_Number] = (uint8_t)(IRQ_Priority<<4);
    }
}

void System_SetPending_PENSV()
{
	uint32_t *Pointer = (uint32_t *)0xE000ED04;
	*Pointer |= (1<<28);
}

void System_ClearPending_PENSV()
{
	uint32_t *Pointer = (uint32_t *)0xE000ED04;
	*Pointer |= (1<<27);
}

void System_SetPending_Systick()
{
	uint32_t *Pointer = (uint32_t *)0xE000ED04;
	*Pointer |= (1<<26);
}

void System_ClearPending_Systick()
{
	uint32_t *Pointer = (uint32_t *)0xE000ED04;
	*Pointer |= (1<<25);
}





