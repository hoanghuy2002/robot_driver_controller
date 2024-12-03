#include "rcc_driver.h"
#include "motor_driver.h"
#include "gpio_driver.h"



#define Motor_Timer_Frequency									1000000U		/* TIM2's Frequency is 1MHz*/
#define Motor_PWM_Frequency										1000U				/* TIM2's PWM Frequency is 1KHz*/	
#define Motor_Timer_NumberCount_To_OverFlow						(uint16_t)(Motor_Timer_Frequency/Motor_PWM_Frequency)
	
#define Motor_Drive_ForwardDirection_1_GPIO_Port				GPIOA	
#define Motor_Drive_ForwardDirection_1_GPIO_Pin					GPIO_Pin0

#define Motor_Drive_ForwardDirection_2_GPIO_Port				GPIOA	
#define Motor_Drive_ForwardDirection_2_GPIO_Pin					GPIO_Pin1

#define Motor_Drive_BackwardDirection_1_GPIO_Port				GPIOA	
#define Motor_Drive_BackwardDirection_1_GPIO_Pin				GPIO_Pin2

#define Motor_Drive_BackwardDirection_2_GPIO_Port				GPIOA	
#define Motor_Drive_BackwardDirection_2_GPIO_Pin				GPIO_Pin3

	
#define Motor_Timer_EnableCLK()									TIM2_EnableCLK()

///////////////////////////////////////////////////////
#define Encoder_Timer_ARR										0xFFFF
#define Encoder_Timer_EnableCLK()								TIM1_EnableCLK()

#define Encoder_Input_Channel_1                                 TIMER_Channel_1

#define Encoder_Input_1_GPIO_Port								GPIOA
#define Encoder_Input_1_GPIO_Pin								GPIO_Pin8




	
static void Configure_Counter_Motor_Timer(void)
{
	Motor_Timer_EnableCLK();
	TIM_ConfigureCounterStruct Timer_Configuration = New_TIM_ConfigureCounterStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_AutoReloadPreload = Enable;
	Timer_Configuration.TIMER_AutoReload = (uint16_t)(Motor_Timer_NumberCount_To_OverFlow - 1);
	Timer_Configuration.TIMER_Counter = 0;
	Timer_Configuration.TIMER_DirectionMode = TIMER_UpCounterMode;
	Timer_Configuration.TIMER_PreScaler =(uint16_t) (GetTimer_Clock(Motor_Timer)/Motor_Timer_Frequency);
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

static void Setup_Motor_Channel_Timer(uint8_t Timer_Channel)
{
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Motor_Timer;
	Timer_Configuration.TIMER_Channel = Timer_Channel;
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
	GPIO_SetMode(Motor_Drive_BackwardDirection_1_GPIO_Port,Motor_Drive_BackwardDirection_1_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	GPIO_SetMode(Motor_Drive_BackwardDirection_2_GPIO_Port,Motor_Drive_BackwardDirection_2_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	GPIO_SetMode(Motor_Drive_ForwardDirection_2_GPIO_Port,Motor_Drive_ForwardDirection_1_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	GPIO_SetMode(Motor_Drive_ForwardDirection_2_GPIO_Port,Motor_Drive_ForwardDirection_2_GPIO_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);
	Configure_Counter_Motor_Timer();
	Configure_Control_Motor_Timer();
	Setup_Motor_Channel_Timer(Motor_Drive_ForwardDirection_1_Channel);
	Setup_Motor_Channel_Timer(Motor_Drive_ForwardDirection_2_Channel);
	Setup_Motor_Channel_Timer(Motor_Drive_BackwardDirection_1_Channel);
	Setup_Motor_Channel_Timer(Motor_Drive_BackwardDirection_2_Channel);
	Motor_Timer_EnableCounter();
}

void Motor_Configure_PWM(uint8_t Motor_Timer_Channel,uint8_t PWM_Percent)
{
	TIM_WriteChannelValue(Motor_Timer,Motor_Timer_Channel,(uint16_t)((PWM_Percent*Motor_Timer_NumberCount_To_OverFlow)/100));
}


static void Configure_Counter_Encoder_Timer(void)
{
	Encoder_Timer_EnableCLK();
	TIM_ConfigureCounterStruct Timer_Configuration = New_TIM_ConfigureCounterStruct;
	Timer_Configuration.Timer = Encoder_Timer;
	Timer_Configuration.TIMER_AutoReloadPreload = Enable;
	Timer_Configuration.TIMER_AutoReload = Encoder_Timer_ARR;
	Timer_Configuration.TIMER_Counter = 0;
	Timer_Configuration.TIMER_DirectionMode = TIMER_UpCounterMode;
	Timer_Configuration.TIMER_PreScaler = 0x0;
	TIM_ConfigureCounter(&Timer_Configuration);
}

static void Configure_Control_Encoder_Timer(void)
{
	TIM_ConfigureControlStruct Timer_Configuration = New_TIM_ConfigureControlStruct;
	Timer_Configuration.Timer = Encoder_Timer;
	Timer_Configuration.TIMER_UpdateEventControl = Enable;
	Timer_Configuration.TIMER_UIF_RequestSource = TIMER_UIF_FromCounter;
	Timer_Configuration.TIMER_TI1_Selection = TIMER_TI1_SelectCH1;
	Timer_Configuration.TIMER_OnePulseMode = Disable;
	TIM_ConfigureControl(&Timer_Configuration);
}

static void Configure_SlaveMode_Encoder_Timer(void)
{
	TIM_ConfigureSlaveModeStruct Timer_Configuration = New_TIM_ConfigureSlaveModeStruct;
	Timer_Configuration.Timer = Encoder_Timer;
	Timer_Configuration.TIMER_SlaveMode = TIMER_ExternalClockMode_1;
	Timer_Configuration.TIMER_TriggerInput = TIMER_TI1FP1;
	TIM_ConfigureSlaveMode(&Timer_Configuration);
}


static void Setup_Encoder_Channel_Timer(uint8_t Timer_Channel)
{
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Encoder_Timer;
	Timer_Configuration.TIMER_Channel = Timer_Channel;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_NoneInverted;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_InputChannelX_X;
	TIM_ConfigureChannel(&Timer_Configuration);
}


uint16_t Encoder_Get_Value(void)
{
	uint16_t Pulse = 0;
	TIM_ReadCountingValue(Encoder_Timer,&Pulse);
	TIM_WriteCountingValue(Encoder_Timer,0);
	return Pulse;
}

void Encoder_Initialization(void)
{
	GPIO_SetMode(Encoder_Input_1_GPIO_Port,Encoder_Input_1_GPIO_Pin,GPIO_Input,GPIO_IP_PUPD);
	Configure_Counter_Encoder_Timer();
	Configure_Control_Encoder_Timer();
	Configure_SlaveMode_Encoder_Timer();
	Setup_Encoder_Channel_Timer(Encoder_Input_Channel_1);
}












