#include "timer_driver.h"
#include "rcc_driver.h"
#include "motor_driver.h"
#include "gpio_driver.h"


#define Motor_Timer															TIM2
#define Motor_Timer_Frequency										1000000U		/* TIM2's Frequency is 1MHz*/
#define Motor_PWM_Frequency											1000U				/* TIM2's PWM Frequency is 1KHz*/	
#define Motor_Timer_NumberCount_To_OverFlow			(Motor_Timer_Frequency/Motor_PWM_Frequency)
	
#define Motor_Drive_Direction_1_GPIO_Port				GPIOA	
#define Motor_Drive_Direction_1_GPIO_Pin				GPIO_Pin0

#define Motor_Drive_Direction_2_GPIO_Port				GPIOA	
#define Motor_Drive_Direction_2_GPIO_Pin				GPIO_Pin1

#define Motor_Drive_InverseDirection_1_GPIO_Port			GPIOA	
#define Motor_Drive_InverseDirection_1_GPIO_Pin				GPIO_Pin2

#define Motor_Drive_InverseDirection_2_GPIO_Port			GPIOA	
#define Motor_Drive_InverseDirection_2_GPIO_Pin				GPIO_Pin3
	
#define Motor_Timer_EnableCLK()					TIM2_EnableCLK()
#define	Motor_Timer_EnableCounter()			TIM2_EnableCounter()
#define Motor_Timer_DisableCounter()		TIM2_DisableCounter()	
	
static void Configure_Counter_Motor_Timer(void)
{
	Motor_Timer_EnableCLK();
	TIM_ConfigureCounterStruct Timer_Configuration = New_TIM_ConfigureCounterStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_AutoReloadPreload = Enable;
	Timer_Configuration.TIMER_AutoReload = (uint16_t)(Motor_Timer_Frequency/Motor_PWM_Frequency) - 1;
	Timer_Configuration.TIMER_Counter = 0;
	Timer_Configuration.TIMER_DirectionMode = TIMER_UpCounterMode;
	Timer_Configuration.TIMER_PreScaler = GetTimer_Clock(Motor_Timer)/Motor_Timer_Frequency;
	TIM_ConfigureCounter(&Timer_Configuration);
}	

static void Configure_Control_Motor_Timer(void)
{
	TIM_ConfigureControlStruct Timer_Configuration = New_TIM_ConfigureControlStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_UpdateEventControl = Enable;
	Timer_Configuration.TIMER_UIF_RequestSource = TIMER_UIF_FromCounter;
	Timer_Configuration.TIMER_TI1_Selection = TIMER_TI1_SelectCH1;
	Timer_Configuration.TIMER_OnePulseMode = Disable;
	TIM_ConfigureControl(&Timer_Configuration);
}

static void Configure_Channel_Motor_Drive_Direction_1_Timer(void)
{
	GPIO_SetMode(Motor_Drive_Direction_1_GPIO_Port,Motor_Drive_Direction_1_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_Channel = Motor_Drive_Direction_1;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_OutputChannel;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_NoneInverted;
	Timer_Configuration.TIMER_OutputCompareFast = Disable;
	Timer_Configuration.TIMER_OutputComparePreload = Enable;
	Timer_Configuration.TIMER_OutputCompareMode = TIMER_PWMMode_1;
	Timer_Configuration.TIMER_OutputCompareClear = Disable;
	TIM_ConfigureChannel(&Timer_Configuration);
}

static void Configure_Channel_Motor_Drive_Direction_2_Timer(void)
{
	GPIO_SetMode(Motor_Drive_Direction_2_GPIO_Port,Motor_Drive_Direction_2_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_Channel = Motor_Drive_Direction_2;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_OutputChannel;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_NoneInverted;
	Timer_Configuration.TIMER_OutputCompareFast = Disable;
	Timer_Configuration.TIMER_OutputComparePreload = Enable;
	Timer_Configuration.TIMER_OutputCompareMode = TIMER_PWMMode_1;
	Timer_Configuration.TIMER_OutputCompareClear = Disable;
	TIM_ConfigureChannel(&Timer_Configuration);
}


static void Configure_Channel_Motor_Drive_InverseDirection_1_Timer(void)
{
	GPIO_SetMode(Motor_Drive_InverseDirection_1_GPIO_Port,Motor_Drive_InverseDirection_1_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_Channel = Motor_Drive_InverseDirection_1;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_OutputChannel;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_NoneInverted;
	Timer_Configuration.TIMER_OutputCompareFast = Disable;
	Timer_Configuration.TIMER_OutputComparePreload = Enable;
	Timer_Configuration.TIMER_OutputCompareMode = TIMER_PWMMode_1;
	Timer_Configuration.TIMER_OutputCompareClear = Disable;
	TIM_ConfigureChannel(&Timer_Configuration);
}

static void Configure_Channel_Motor_Drive_InverseDirection_2_Timer(void)
{
	GPIO_SetMode(Motor_Drive_InverseDirection_2_GPIO_Port,Motor_Drive_InverseDirection_2_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_Channel = Motor_Drive_InverseDirection_2;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_OutputChannel;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_NoneInverted;
	Timer_Configuration.TIMER_OutputCompareFast = Disable;
	Timer_Configuration.TIMER_OutputComparePreload = Enable;
	Timer_Configuration.TIMER_OutputCompareMode = TIMER_PWMMode_1;
	Timer_Configuration.TIMER_OutputCompareClear = Disable;
	TIM_ConfigureChannel(&Timer_Configuration);
}

void Motor_Initialization(void)
{
	GPIO_SetMode(Motor_Drive_Direction_1_GPIO_Port,Motor_Drive_Direction_1_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	GPIO_SetMode(Motor_Drive_Direction_2_GPIO_Port,Motor_Drive_Direction_2_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	Configure_Counter_Motor_Timer();
	Configure_Control_Motor_Timer();
	Configure_Channel_Motor_Drive_Direction_1_Timer();
	Configure_Channel_Motor_Drive_Direction_2_Timer();
	Motor_Timer_EnableCounter();
}

void Motor_Configure_PWM(uint8_t Motor_Timer_Channel,uint8_t PWM_Percent)
{
	TIM_WriteChannelValue(Motor_Timer,Motor_Timer_Channel,(uint16_t)((PWM_Percent*Motor_Timer_NumberCount_To_OverFlow)/100));
}



