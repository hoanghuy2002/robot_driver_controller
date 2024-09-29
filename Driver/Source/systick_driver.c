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
    HCLK =SystemClock_Value;
    SYSTICK->ControlStatus_Register |= (1<<2);
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


void Setup_SystickIRQ_Ms(uint32_t MiliSecond)
{
	uint32_t Counter = MiliSecond*(HCLK/1000);
	SYSTICK->CurrentValue_Register = 0;
	SYSTICK->ReloadValue_Register = Counter;
	SYSTICK->ControlStatus_Register = 6;
	
}

void Setup_SystickIRQ_Us(uint32_t MicroSecond)
{
	uint32_t Counter = MicroSecond*(HCLK/1000000);
	SYSTICK->CurrentValue_Register = 0;
	SYSTICK->ReloadValue_Register = Counter;
	SYSTICK->ControlStatus_Register |= 0x02;
}



