#include "millisecond.h"
#include "rcc_driver.h"

#define MilliSecond_Timer										TIM4
#define MilliSecond_Timer_Frequency								10000U //1000Hz	

#define MilliSecond_EnableCLK()									TIM4_EnableCLK()
#define MilliSecond_EnableCounter()								TIM4_EnableCounter()
#define MilliSecond_DisableCounter()							TIM4_DisableCounter()

static void Timer_Counter_Setup(void)
{
	TIM_ConfigureCounterStruct Custom_Timer = New_TIM_ConfigureCounterStruct;
	Custom_Timer.Timer = MilliSecond_Timer;
	Custom_Timer.TIMER_AutoReloadPreload = Enable;
	Custom_Timer.TIMER_DirectionMode = TIMER_UpCounterMode;
	Custom_Timer.TIMER_PreScaler = (uint16_t)(GetTimer_Clock(MilliSecond_Timer)/MilliSecond_Timer_Frequency);
	Custom_Timer.TIMER_AutoReload = 0xFFFF;
	TIM_ConfigureCounter(&Custom_Timer);
}


void MilliSecond_Setup()
{
	MilliSecond_EnableCLK();
	Timer_Counter_Setup();
}

void MilliSecond_Start(void)
{
	MilliSecond_EnableCounter();
	TIM_WriteCountingValue(MilliSecond_Timer,0);
}

uint16_t MilliSecond_Stop(void)
{
	uint16_t data = 0;
	TIM_ReadCountingValue(MilliSecond_Timer,&data);
	MilliSecond_DisableCounter();
	data = data/10;
	return data;
}
