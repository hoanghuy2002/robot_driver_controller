#include "ultrasonic.h"
#include "gpio_driver.h"
#include "timer_driver.h"
#include "rcc_driver.h"


#define Ultrasonic_Timer										TIM3
#define Ultrasonic_Timer_Frequency								1000000U

#define Ultrasonic_Left_GPIO_Port								GPIOA
#define Ultrasonic_Left_GPIO_Pin								GPIO_Pin6

#define Ultrasonic_Center_GPIO_Port								GPIOA
#define Ultrasonic_Center_GPIO_Pin								GPIO_Pin7

#define Ultrasonic_Right_GPIO_Port								GPIOB
#define Ultrasonic_Right_GPIO_Pin								GPIO_Pin0

#define Ultrasonic_Trigger_Port 								GPIOB
#define Ultrasonic_Trigger_Pin									GPIO_Pin1

#define Ultrasonic_Timer_EnableCLK()						TIM3_EnableCLK()
#define Ultrasonic_Timer_EnableCounter()					TIM3_EnableCounter()
#define Ultrasonic_Timer_DisableCounter()					TIM3_DisableCounter()

#define Start_Trigger_Time					 				0x089AU

static void Configure_Counter_Ultrasonic_Timer(void)
{
	Ultrasonic_Timer_EnableCLK();
	TIM_ConfigureCounterStruct Timer_Configuration = New_TIM_ConfigureCounterStruct;
	Timer_Configuration.Timer = Ultrasonic_Timer;
	Timer_Configuration.TIMER_AutoReloadPreload = Enable;
	Timer_Configuration.TIMER_AutoReload = 0xFFFF;
	Timer_Configuration.TIMER_DirectionMode = TIMER_UpCounterMode;
	Timer_Configuration.TIMER_PreScaler = GetTimer_Clock(Ultrasonic_Timer)/Ultrasonic_Timer_Frequency;	/*Configure Ultrasonic_Timer's Frequency is 1MHz*/
	TIM_ConfigureCounter(&Timer_Configuration);
}

static void Configure_Control_Ultrasonic_Timer(void)
{
	TIM_ConfigureControlStruct Timer_Configuration = New_TIM_ConfigureControlStruct;
	Timer_Configuration.Timer = Ultrasonic_Timer;
	Timer_Configuration.TIMER_UpdateEventControl = Enable;
	Timer_Configuration.TIMER_UIF_RequestSource = TIMER_UIF_FromCounter;
	Timer_Configuration.TIMER_TI1_Selection = TIMER_TI1_SelectCH1;
	Timer_Configuration.TIMER_OnePulseMode = Disable;
	TIM_ConfigureControl(&Timer_Configuration);
}



static void Configure_Channel_Ultrasonic_Left_Timer(void)
{
	GPIO_SetMode(Ultrasonic_Left_GPIO_Port,Ultrasonic_Left_GPIO_Pin,GPIO_Input,GPIO_IP_PUPD);			/*Enable GPIO for Channel*/
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Ultrasonic_Timer;
	Timer_Configuration.TIMER_Channel = Ultrasonic_Left;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_InputChannelX_X;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_Inverted;
	Timer_Configuration.TIMER_InputCaptureFillter = TIMER_fckINT_2Event;
	TIM_ConfigureChannel(&Timer_Configuration);
}


static void Configure_Channel_Ultrasonic_Center_Timer(void)
{
	GPIO_SetMode(Ultrasonic_Center_GPIO_Port,Ultrasonic_Center_GPIO_Pin,GPIO_Input,GPIO_IP_PUPD);			/*Enable GPIO for Channel*/
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Ultrasonic_Timer;
	Timer_Configuration.TIMER_Channel = Ultrasonic_Center;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_InputChannelX_X;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_Inverted;
	Timer_Configuration.TIMER_InputCaptureFillter = TIMER_fckINT_2Event;
	TIM_ConfigureChannel(&Timer_Configuration);
}


static void Configure_Channel_Ultrasonic_Right_Timer(void)
{
	GPIO_SetMode(Ultrasonic_Right_GPIO_Port,Ultrasonic_Right_GPIO_Pin,GPIO_Input,GPIO_IP_PUPD);			/*Enable GPIO for Channel*/
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Ultrasonic_Timer;
	Timer_Configuration.TIMER_Channel = Ultrasonic_Right;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_InputChannelX_X;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_Inverted;											
	Timer_Configuration.TIMER_InputCaptureFillter = TIMER_fckINT_2Event;
	TIM_ConfigureChannel(&Timer_Configuration);
}

static void Configure_Channel_Ultrasonic_Trigger_Timer(void)
{
	GPIO_SetMode(Ultrasonic_Trigger_Port,Ultrasonic_Trigger_Pin,GPIO_Output_10MHz,GPIO_OP_AFPP);			/*Enable GPIO for Channel*/
	TIM_ConfigureChannelStruct Timer_Configuration = New_TIM_ConfigureChannelStruct;
	Timer_Configuration.Timer = Ultrasonic_Timer;
	Timer_Configuration.TIMER_Channel = Ultrasonic_Trigger_Channel;
	Timer_Configuration.TIMER_ChannelDirection = TIMER_OutputChannel;
	Timer_Configuration.TIMER_ChannelPolarity = TIMER_NoneInverted;
	Timer_Configuration.TIMER_OutputCompareMode = TIMER_PWMMode_1;
	Timer_Configuration.TIMER_OutputComparePreload = Enable;
	TIM_ConfigureChannel(&Timer_Configuration);
}


void Ultrasonic_Initialization(void)
{
	Configure_Counter_Ultrasonic_Timer();
	Configure_Control_Ultrasonic_Timer();
	Configure_Channel_Ultrasonic_Left_Timer();
	Configure_Channel_Ultrasonic_Center_Timer();
	Configure_Channel_Ultrasonic_Right_Timer();
	Configure_Channel_Ultrasonic_Trigger_Timer();
}
void Ultrasonic_Trigger(void)
{
	TIM_WriteChannelValue(Ultrasonic_Timer,Ultrasonic_Trigger_Channel,0xFFF);
	TIM_WriteCountingValue(Ultrasonic_Timer,0);
	Ultrasonic_Timer_EnableCounter();
	// TIM_WriteChannelValue(Ultrasonic_Timer,Ultrasonic_Trigger_Channel,0xFFFF);
}

float Ultrasonic_Get_Distance(uint8_t Ultrasonic_Channel)
{
	volatile uint16_t Data =0;
	if(TIM_ReadFlag(Ultrasonic_Timer,Ultrasonic_Channel+1)==1)
	{
		Data = TIM_ReadChannelValue(Ultrasonic_Timer,Ultrasonic_Channel);
		return (float)((Data-Start_Trigger_Time)/58.0);
	}
	else return 1000.0;
}


