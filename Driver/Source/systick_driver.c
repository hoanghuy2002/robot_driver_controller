#include "systick_driver.h"
#include "cortexm3_irq.h"
#include "cortexm3.h"

static uint32_t HCLK;

/*********************************************************************
 * @fn      		  		- SystickTimer_Init
 *
 * @brief             - This function to Init SystickTimer (set value HCLK, enable/disable IRQ)
 *
 * @param[1]          - HCLK:System Clock's Frequency 
 * @param[2]          - IRQ:Disable/Enable IRQ When Systick time's buffer overflow
 *
 * @return            -  none
 *
 * @Note              -  none

 */
void SystickTimer_Init(uint32_t SystemClock_Value)
{
    HCLK =SystemClock_Value/8;
    SYSTICK->ControlStatus_Register |= (1<<4);
}

void SystickTimer_DeInit()
{

		SYSTICK->ControlStatus_Register =0;
}

void SysTick_DelayMs(uint32_t MiliSecond)
{
	uint32_t Counter = (HCLK/1000);
	SYSTICK->ReloadValue_Register = Counter;
	SYSTICK->CurrentValue_Register = Counter;
	SYSTICK->ControlStatus_Register |= (1<<0);
	for(uint32_t i=0;i<MiliSecond;i++)
	{
		while((SYSTICK->ControlStatus_Register & (1<<16))==0);
	}
	SYSTICK->ControlStatus_Register &= ~(uint32_t)(1<<0);
}

void SysTick_DelayUs(uint32_t MicroSecond)
{
	uint32_t Counter = (HCLK/1000000);
	SYSTICK->ReloadValue_Register = Counter;
	SYSTICK->CurrentValue_Register = Counter;
	SYSTICK->ControlStatus_Register |= (1<<0);
	for(uint8_t i=0;i<MicroSecond;i++)
	{
		while((SYSTICK->ControlStatus_Register&(1<<16))==0);
	}
	SYSTICK->ControlStatus_Register &= ~(uint32_t)(1<<0);
}


void SystickIRQ_Ms(uint32_t MiliSecond)
{
	Disable_IRQ();
	uint32_t Counter = MiliSecond*(HCLK/1000);
	uint32_t *Pointer = (uint32_t *)0xE000E014;
	*Pointer = Counter-1;
	Pointer = (uint32_t *)0xE000E018;
	*Pointer =0;
	Pointer = (uint32_t *)0xE000E010;
	*Pointer = 0x07;
	Enable_IRQ();
	
}

void SystickIRQ_Us(uint32_t MicroSecond)
{
	Disable_IRQ();
	uint32_t Counter = MicroSecond*(HCLK/1000000);
	uint32_t *Pointer = (uint32_t *)0xE000E014;
	*Pointer = Counter-1;
	Pointer = (uint32_t *)0xE000E018;
	*Pointer =0;
	Pointer = (uint32_t *)0xE000E010;
	*Pointer = 0x07;
	Enable_IRQ();
}


