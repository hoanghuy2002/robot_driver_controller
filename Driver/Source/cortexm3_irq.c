
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
	

void NVIC_Enable_IRQ(uint8_t NVIC_IRQ_Number)
{
	
  NVIC->SetEnable_IRQ[NVIC_IRQ_Number/32] |= (uint32_t)(1<<(NVIC_IRQ_Number-(NVIC_IRQ_Number/32)*32));
}

void NVIC_Disable_IRQ(uint8_t NVIC_IRQ_Number)
{
    NVIC->ClearEnable_IRQ[NVIC_IRQ_Number/32] |= (uint32_t)(1<<(NVIC_IRQ_Number-(NVIC_IRQ_Number/32)*32));
}

void NVIC_SetPending_IRQ(uint8_t NVIC_IRQ_Number)
{
    NVIC->SetPending_IRQ[NVIC_IRQ_Number/32] |= (uint32_t)(1<<(NVIC_IRQ_Number-(NVIC_IRQ_Number/32)*32));
}


void NVIC_SetPriority_IRQ(uint8_t NVIC_IRQ_Number, uint8_t NVIC_IRQ_Priority)
{
    if (NVIC_IRQ_Priority <= 15)
    {
      NVIC->IRQPriority[NVIC_IRQ_Number] = (uint8_t)(NVIC_IRQ_Priority<<4);
    }
}

void System_SetPriority_IRQ(uint8_t System_IRQ_Number,uint8_t System_IRQ_Priority)
{
	uint32_t *Pointer = (uint32_t *)0xE000ED18;
	uint8_t Position = 0;
	Position = (uint32_t)((System_IRQ_Number-4)/4);
	*(Pointer+Position) &= ~(0xFF<<(System_IRQ_Number%4*8));
	*(Pointer+Position) |= (System_IRQ_Priority<<(System_IRQ_Number%4*8+4));
}

void System_SetPending_PendSV()
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





