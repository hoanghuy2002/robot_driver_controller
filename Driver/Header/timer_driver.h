#ifndef _TIMER_DRIVER_H_
#define _TIMER_DRIVER_H_

#include <stdint.h>
#include "stm32f103.h"

#define TIM1_EnableCLK()			(RCC->APB2ENR |= (1<<11))
#define TIM8_EnableCLK()			(RCC->APB2ENR |= (1<<13))
#define TIM9_EnableCLK()			(RCC->APB2ENR |= (1<<19))
#define TIM10_EnableCLK()			(RCC->APB2ENR |= (1<<20))
#define TIM11_EnableCLK()			(RCC->APB2ENR |= (1<<21))
#define TIM2_EnableCLK()			(RCC->APB1ENR |= (1<<0))
#define TIM3_EnableCLK()			(RCC->APB1ENR |= (1<<1))
#define TIM4_EnableCLK()			(RCC->APB1ENR |= (1<<2))
#define TIM5_EnableCLK()			(RCC->APB1ENR |= (1<<3))
#define TIM6_EnableCLK()			(RCC->APB1ENR |= (1<<4))
#define TIM7_EnableCLK()			(RCC->APB1ENR |= (1<<5))
#define TIM12_EnableCLK()			(RCC->APB1ENR |= (1<<6))
#define TIM13_EnableCLK()			(RCC->APB1ENR |= (1<<7))
#define TIM14_EnableCLK()			(RCC->APB1ENR |= (1<<8))


#define TIM1_DisableCLK()			(RCC->APB2ENR &= ~(uint32_t)(1<<11))
#define TIM8_DisableCLK()			(RCC->APB2ENR &= ~(uint32_t)(1<<13))
#define TIM9_DisableCLK()			(RCC->APB2ENR &= ~(uint32_t)(1<<19))
#define TIM10_DisableCLK()		(RCC->APB2ENR &= ~(uint32_t)(1<<20))
#define TIM11_DisableCLK()		(RCC->APB2ENR &= ~(uint32_t)(1<<21))
#define TIM2_DisableCLK()			(RCC->APB1ENR &= ~(uint32_t)(1<<0))
#define TIM3_DisableCLK()			(RCC->APB1ENR &= ~(uint32_t)(1<<1))
#define TIM4_DisableCLK()			(RCC->APB1ENR &= ~(uint32_t)(1<<2))
#define TIM5_DisableCLK()			(RCC->APB1ENR &= ~(uint32_t)(1<<3))
#define TIM6_DisableCLK()			(RCC->APB1ENR &= ~(uint32_t)(1<<4))
#define TIM7_DisableCLK()			(RCC->APB1ENR &= ~(uint32_t)(1<<5))
#define TIM12_DisableCLK()		(RCC->APB1ENR &= ~(uint32_t)(1<<6))
#define TIM13_DisableCLK()		(RCC->APB1ENR &= ~(uint32_t)(1<<7))
#define TIM14_DisableCLK()		(RCC->APB1ENR &= ~(uint32_t)(1<<8))

#define TIM1_EnableCounter()		(TIM1->CR1 |= (1<<0))
#define TIM2_EnableCounter()		(TIM2->CR1 |= (1<<0))
#define TIM3_EnableCounter()		(TIM3->CR1 |= (1<<0))
#define TIM4_EnableCounter()		(TIM4->CR1 |= (1<<0))
#define TIM5_EnableCounter()		(TIM5->CR1 |= (1<<0))
#define TIM6_EnableCounter()		(TIM6->CR1 |= (1<<0))
#define TIM7_EnableCounter()		(TIM7->CR1 |= (1<<0))
#define TIM8_EnableCounter()		(TIM8->CR1 |= (1<<0))
#define TIM9_EnableCounter()		(TIM9->CR1 |= (1<<0))
#define TIM10_EnableCounter()		(TIM10->CR1 |= (1<<0))
#define TIM11_EnableCounter()		(TIM11->CR1 |= (1<<0))
#define TIM12_EnableCounter()		(TIM12->CR1 |= (1<<0))
#define TIM13_EnableCounter()		(TIM13->CR1 |= (1<<0))
#define TIM14_EnableCounter()		(TIM14->CR1 |= (1<<0))

#define TIM1_DisableCounter()		(TIM1->CR1 &= 0xFFFE)
#define TIM2_DisableCounter()		(TIM2->CR1 &= 0xFFFE)
#define TIM3_DisableCounter()		(TIM3->CR1 &= 0xFFFE)
#define TIM4_DisableCounter()		(TIM4->CR1 &= 0xFFFE)
#define TIM5_DisableCounter()		(TIM5->CR1 &= 0xFFFE)
#define TIM6_DisableCounter()		(TIM6->CR1 &= 0xFFFE)
#define TIM7_DisableCounter()		(TIM7->CR1 &= 0xFFFE)
#define TIM8_DisableCounter()		(TIM8->CR1 &= 0xFFFE)
#define TIM9_DisableCounter()		(TIM9->CR1 &= 0xFFFE)
#define TIM10_DisableCounter()	(TIM10->CR1 &= 0xFFFE)
#define TIM11_DisableCounter()	(TIM11->CR1 &= 0xFFFE)
#define TIM12_DisableCounter()	(TIM12->CR1 &= 0xFFFE)
#define TIM13_DisableCounter()	(TIM13->CR1 &= 0xFFFE)
#define TIM14_DisableCounter()	(TIM14->CR1 &= 0xFFFE)




typedef enum
{
	TIM_ParameterError = -1,
	TIM_Error					 =  0, 
	TIM_Success				 =	1,
}TIM_Status;


typedef struct
{
	TIM_RegStruct *Timer;																			/*Specifies the Timer 
																														--- parameter: TIM1 To TIM14*/ 
	uint16_t TIMER_Counter;																		/*Specifies value of counter Register
																														---- parameter: interger number min = 0x00, max = 0xFFFF */
	uint16_t TIMER_AutoReload;																/*Specifies value of Auto-reload Register
																														---- parameter: interger number min = 0x00, max = 0xFFFF */
	uint16_t TIMER_PreScaler;																	/*Specifies value of Prescaler Register
																														---- parameter: interger number min = 0x00, max = 0xFFFF */
	uint8_t  TIMER_RepetitionCounter;													/*Specifies value of Repetition Counter Register
																														*****Only avaiable for TIM1 or TIM8 
																														---- parameter: interger number min = 0x00, max = 0xFF */
	uint8_t  TIMER_AutoReloadPreload;													/*Specifies the option about Preload value of Auto-reload
																														---- parameter: Enable or Disable */					
	uint8_t  TIMER_DirectionMode;															/*Specifies the option about Direction of Counter
																														*****Only avaiable for TIM1 to TIM5 and TIM8
																														---- parameter: @ref define_TIMER_DirectionMode */	
}TIM_ConfigureCounterStruct;

/*Make sure initialize this structure with the structure parameter New_TIM_ConfigureCounterStruct
	e.g TIM_ConfigureCounterStruct TimerCustom = New_TIM_ConfigureCounterStruct*/


/**************************************************************************/


typedef struct
{
	TIM_RegStruct *Timer;																			/*Specifies the Timer 
																														--- parameter: TIM1 To TIM14*/ 
	uint8_t TIMER_ClockDivision;															/*Specifies the division ratio between the timer clock frequency and the dead-time and sampling 
																															clock used by dead-time generators and the digital filters
																														--- parameter: @ref define_TIMER_ClockDivision*/ 
	uint8_t TIMER_UpdateEventControl;													/*Specifies the update event generation. 
																														-If Enable The Update event (UEV) is generated by one of the following events(Counter overflow/
																															underflow - setting the UG bit - Update generation through the slave mode controller). 
																														-If Disable the update event (UEV) is not generated.
																														--- parameter: "Enable" or "Disable"*/		
	uint8_t TIMER_UIF_RequestSource;													/*Specifies the Event source can update the UIF Flag to generate Interrupt or DMA request
																														--- parameter: @ref define_TIMER_UIF_RequestSource*/ 
	uint8_t TIMER_OnePulseMode;																/*Specifies the option to select the One Pulse Mode
																														if Enable The Counter will stop at the next update event
																														--- parameter: "Enable" or "Disable"*/ 
	uint8_t TIMER_TI1_Selection;															/*Specifies the Channel Selection for TI1
																														*****Avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8
																														--- parameter: @ref define_TIMER_TI1_Selection*/
	uint8_t TIMER_MasterMode;																	/*Specifies the information selection to be send in master mode to slaver timer in
																															for synchronization
																														*****Avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8
																														--- parameter: @ref define_TIMER_MasterMode*/
}TIM_ConfigureControlStruct;

/*Make sure initialize this structure with the structure parameter New_TIM_ConfigureControlStruct
	e.g TIM_ConfigureControlStruct TimerCustom = New_TIM_ConfigureControlStruct*/


/**************************************************************************/


typedef struct
{
	TIM_RegStruct *Timer;																			/*Specifies the Timer 
																														--- parameter: TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM12*/
	uint8_t TIMER_SlaveMode;																	/*Specifies the Selection of Slave Mode
																														*****Avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 -TIM12
																														--- parameter: @ref define_TIMER_SlaveMode - default Slave Mode Disable*/
	uint8_t TIMER_TriggerInput;																/*Specifies the Selection of Trigger Input use to Slave Mode
																														*****Avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 -TIM12
																														--- parameter: @ref define_TIMER_TriggerInput - default Internal Trigger 0*/
	uint8_t TIMER_ExternalClockMode_2;												/*Specifies the configure to use External Clock Mode 2
																														if External Clock Mode 2 is enable then all slave mode will be disable and the counter can 
																															 count at each rising or falling edge on external trigger input (ETRF)(external trigger 
																															 input after fillter, polarity and prescaler)
																														****Avaiable for TIM1 - TIM2 - TIM8
																														--- parameter: "Enable" or "Disable"*/
	uint8_t TIMER_ExternalTriggerPolarity;										/*Specifies the level or edge of External Trigger Input channel to active
																														****Avaiable for TIM1 - TIM2 - TIM8
																														--- parameter: @ref define_TIMER_Polarity - default active on high level or rising edge*/
	uint8_t TIMER_ExternalTriggerPrescaler;										/*Specifies the prescaler to reduce frequency of External Trigger Input channel
																														*****Avaiable for TIM1 - TIM2 - TIM8.
																														--- parameter: @ref define_TIMER_ChannelPrescaler - default Prescaler Off*/
	uint8_t TIMER_ExternalTriggerFillter;											/*Specifies the frequency use to sample ETRP signal and number consecutive event need to 
																															validate the transition
																														*****Avaiable for TIM1 - TIM2 - TIM8
																														--- parameter: @ref define_TIMER_ChannelFillter - default No Fillter*/
																																			
}TIM_ConfigureSlaveModeStruct;


/*Make sure initialize this structure with the structure parameter New_TIM_ConfigureSlaveModeStruct
	e.g TIM_ConfigureSlaveModeStruct TimerCustom = New_TIM_ConfigureSlaveModeStruct*/


/**************************************************************************/


typedef struct
{
	TIM_RegStruct *Timer;																			/*Specifies the Timer 
																														--- parameter: TIM1 to TIM14 except TIM6 and TIM7*/
	uint8_t TIMER_Channel;																		/*Specifies the channel to run input capture mode or out compare mode 	
																														--- parameter: @ref define_TIMER_Channel - default:Channel 1 is selected */
	uint8_t TIMER_ChannelDirection;														/*Specifies the diretion for channel, Input or Output
																														--- parameter: @ref define_TIMER_ChannelDirection - default:Channel is Output */
	uint8_t TIMER_ChannelPolarity;														/*Specifies level or edge to active the channel
																														--- parameter: @ref define_TIMER_Polarity - default active on high level or rising edge*/
	uint8_t TIMER_ComplementaryChannelPolarity;								/*Specifies level or edge to active the complementary of channel
																														***** avaiable for TIM1 - TIM8
																														--- parameter: @ref define_TIMER_Polarity - default active on high level or rising edge*/
	uint8_t TIMER_InputCapturePrescaler;											/*Specifies the number event to detected input capture
																														***** avaiable when Channel is configured as input. If channel is configured as output 
																																	then make sure don't configure this parameter.
																														--- parameter: @ref define_TIMER_ChannelPrescaler - default Prescaler Off*/
	uint8_t TIMER_InputCaptureFillter;												/*Specifies the frequency use to sample input signal and number consecutive event need to 
																															validate the transition
																														***** avaiable avaiable when Channel is configured as input. If channel is configured as output 
																																	then make sure don't configure this parameter.
																														--- parameter: @ref define_TIMER_ChannelFillter - default No Fillter*/
	uint8_t TIMER_OutputCompareFast;													/*Specified reduce number clock cycles delay to active output channel when edge occur 
																															on the trigger input
																														If Disable then minimum number clock cycles delay is 5
																														If Enable then minimum number clock cycles delay is 3
																														***** avaiable when channel is configured as output. If channel is configured as input then
																																	make sure don't configured this parameter
																														--- parameter: "Enable" or "Disable" - default: Disable*/
	uint8_t TIMER_OutputComparePreload;												/*Specifies The effect when write new value compare to Capture/Compare Register(CCRx)
																														If Disable then CCRx can be written any time. the new value is taken into account immediately
																														If Enable then the new value is written to CCRx is taken into account at each update event
																														***** avaiable when channel is configured as output. If channel is configured as input then
																																	make sure don't configured this parameter
																														--- parameter: "Enable" or "Disable" - default: Disable*/
	uint8_t TIMER_OutputCompareMode;													/*Specifies The behavior of the output referrence signal (OCxREF)(The output signal before 
																															output channel polarity).
																														***** avaiable when channel is configured as output. If channel is configured as input then
																																	make sure don't configured this parameter
																														--- parameter: @ref define_TIMER_OutputCompareMode - default: Frozen Mode*/
	uint8_t TIMER_OutputCompareClear;													/*Specifies the effect to OCxREF by the External Trigger Input(ETRF)
																															If Disable then OCxREF is not affected by the External Trigger Input(ETRF)
																															If Enable then OCxREF is cleared as soon as High level is detected on the ETRF input
																														***** avaiable when channel is configured as output. If channel is configured as input then
																																	make sure don't configured this parameter
																														***** avaiable for TIM1 - TIM2 - TIM8
																														--- parameter: "Enable" or "Disable" - default: Disable*/
}TIM_ConfigureChannelStruct;

/*Make sure initialize this structure with the structure parameter New_TIM_ConfigureChannelStruct
	e.g TIM_ConfigureChannelStruct TimerCustom = New_TIM_ConfigureChannelStruct*/



/**************************************************************************/
/**************************************************************************/
/**************************************************************************/


/*The parameter to Initialize Timer's Struct*/
#define New_TIM_ConfigureCounterStruct						{0,0,0,0,0,0,0}						/*Use to initialize member of TIM_ConfigureCounterStruct*/
#define New_TIM_ConfigureControlStruct						{0,0,0,0,0,0,0}						/*Use to initialize member of TIM_ConfigureControlStruct*/
#define New_TIM_ConfigureSlaveModeStruct					{0,0,0,0,0,0,0}						/*Use to initialize member of TIM_ConfigureSlaveModeStruct*/
#define New_TIM_ConfigureChannelStruct						{0,0,0,0,0,0,0,0,0,0,0}		/*Use to initialize member of TIM_ConfigureChannelStruct*/

/*define_TIMER_DirectionMode*/

#define TIMER_UpCounterMode							1U
#define TIMER_DownCounterMode						2U
#define TIMER_CenterAlignedMode1				3U
#define TIMER_CenterAlignedMode2				5U
#define TIMER_CenterAlignedMode3				7U


/**************/


/*define_TIMER_ClockDivision*/
#define TIMER_tDTS_tCK_INT							0U									/* tDTS = tCLK_Internal*/
#define TIMER_tDTS_2tCK_INT							1U									/* tDTS = 2tCLK_Internal*/
#define TIMER_tDTS_4tCK_INT							2U									/* tDTS = 4tCLK_Internal*/


/**************/


/*define_TIMER_UIF_RequestSource*/
#define TIMER_UIF_FromBasicEvent				0U									/*All event (Counter overflow/underflow - setting the UG bit - Update generation 
																														through the slave mode controller) will setting the UIF bit (generate the update interrupt
																														or DMA request)*/
#define TIMER_UIF_FromCounter						1U									/*Only Event Counter overflow/underflow setting the UIF bit*/


/**************/


/*define_TIMER_TI1_Selection*/
#define TIMER_TI1_SelectCH1					  0U									/*The Channel CH1 is selected for TI1(Timer Input 1) input*/
#define TIMER_TI1_SelectCH123					1U									/*CH1 - CH2 - CH3 are connected to the TI1 input (XOR Combination)*/ 


/**************/


/*define_TIMER_MasterMode*/
#define TIMER_MasterMode_Reset							0U
#define TIMER_MasterMode_Enable							1U
#define TIMER_MasterMode_Update							2U
#define TIMER_MasterMode_ComparePulse				3U
#define TIMER_MasterMode_Compare_OC1REF			4U
#define TIMER_MasterMode_Compare_OC2REF			5U
#define TIMER_MasterMode_Compare_OC3REF			6U
#define TIMER_MasterMode_Compare_OC4REF			7U


/**************/


/*define_TIMER_SlaveMode*/
#define TIMER_SlaveModeDisable			0U			/*The prescaler is clocked directly by the internal clock*/
#define TIMER_EncoderMode_1					1U			/*The Counter counts up/down only on TI2FP1 Edge(Input Capture 2 maped on Timer input 2 after fillter and polarity) 
																						depending on level of TI1FP2 (Input Capture 2 maped on Timer input 1 after fillter and polarity)
																						***** Not avaiable for TIM9 and TIM12 */
#define TIMER_EncoderMode_2					2U			/*The Counter counts up/down only on TI1FP2 Edge(Input Capture 2 maped on Timer input 1 after fillter and polarity) 
																						depending on level of TI2FP1 (Input Capture 2 maped on Timer input 1 after fillter and polarity)
																						***** Not avaiable for TIM9 and TIM12 */
#define TIMER_EncoderMode_3					3U			/*The counter counts up/down on TI1FP1 Edge(Input capture 1 maped on timer input 1 after fillter and polarity)
																						depending on level of TI2FP2 (Input Capture 2 maped on timer inpput 2 after fillter and polarity)
																						and counts up/down on TI2FP2 Edge(Input capture 2 maped on timer input 2 after fillter and polarity)
																						depending on level of TI1FP1(Input capture 1 maped on timer input 1 after fillter and polarity)
																						***** Not avaiable for TIM9 and TIM12 */
#define TIMER_ResetMode							4U			/*Rising edge of the Selected Trigger Input (TRGI) reinitializes the counter 
																						and generates the update of the register*/
#define TIMER_GatedMode							5U			/*The counter start depending Counter Clock when the Selected Trigger Input (TRGI) is High. 
																						The counter stop (But does not reset counter register) as soon as the Selected Trigger Input (TRGI) becomes low
																						Counter Start and stop both are controled by the Selected Trigger Input (TRGI)
																						***** must not be used if TI1F_ED is selected as the trigger input*/
#define TIMER_TriggerMode						6U			/*The counter start depending Counter Clock when the Selected Trigger Input (TRGI) is High. 
																						On The Counter start is controled by the Selected Trigger Input (TRGI)*/
#define TIMER_ExternalClockMode_1		7U			/*The counter counts depending the rising edge of the Selected Trigger Input (TRGI)*/ 


/**************/


/*define_TIMER_TriggerInput*/
#define TIMER_ITR0									0U			/*Internal Trigger 0*/
#define TIMER_ITR1									1U			/*Internal Trigger 1*/
#define TIMER_ITR2									2U			/*Internal Trigger 2*/
#define TIMER_ITR3									3U			/*Internal Trigger 3*/
#define TIMER_TI1F_ED								4U			/*Timer Input 1 Edge detector*/
#define TIMER_TI1FP1								5U			/*Input capture 1 maped on Timer Input 1 after fillter and polarity*/
#define TIMER_TI2FP2								6U			/*Input capture 2 maped on Timer Input 2 after fillter and polarity*/
#define TIMER_ETRF									7U			/*External trigger Channel after fillter, prescaler, and polarity
																						***** TIMER_ETRF only avaiable for TIM1, TIM2 and TIM8*/

/**************/


/*define_TIMER_Channel*/
#define TIMER_Channel_1										0U				/*Channel l is selected to Configure
																										***** avaiable for all Timer*/
#define TIMER_Channel_2										1U				/*Channel 2 is selected to Configure
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM12*/
#define TIMER_Channel_3										2U				/*Channel 3 is selected to Configure
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8*/
#define TIMER_Channel_4										3U				/*Channel 4 is selected to Configure
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8*/
																										
																										
/**************/


/*define_TIMER_ChannelDirection*/
#define TIMER_OutputChannel								0U			 /*Channel is configure as output*/
#define TIMER_InputChannelX_X							1U			 /*Channel is configure as input and input capture mapped on this channel
																									 e.g. Channel 1 is configure as input and IC1 mapped on TI1*/
#define TIMER_InputChannelX_Y							2U			 /*Channel is configure as input and input capture mapped on opposite channel  (1-2 and 3-4)
																									 e.g Channel 2 is configure as input and IC2 mapped on TI1 and vice versa (Channel 1 is configure 
																									 as input and IC1 mapped on TI2).
																									 e.g Channel 3 is configure as input and IC2 mapped in TI4 and vice versa
																									 ***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM12*/
#define TIMER_InputChannel_TRC						3U			 /*Channel is configure as input and input capture mapped on TRC
																									 This feature only avaiable when Internal trigger is selected as Trigger input*/

/**************/


/*define_TIMER_OutputCompareMode*/
#define TIMER_FrozenMode									0U				/*The comparision between counter register (CNT) and capture/compare register (CCRx) has no effect
																											on the output*/
#define TIMER_ActiveLevelMode							1U				/*OCxREF force High (Set channel to active level) when the counter register (CNT) match the 
																											the capture/compare register (CCRx).*/
#define TIMER_InActiveLevelMode					  2U				/*OCxREF force Low (Set channel to inactive level) when the counter register (CNT) match the 
																											the capture/compare register (CCRx)  (CNT = CCRx).*/																					
#define TIMER_ToggleMode									3U				/*The level of OCxREF is toggle when the counter register (CNT) match the 
																											the capture/compare register (CCRx).  (CNT = CCRx)*/
#define TIMER_ForceActiveLevelMode				4U				/*The level of OCxREF is alway high (channel alway is active)*/
#define TIMER_ForceInActiveLevelMode			5U				/*The level of OCxREF is alway low (channel alway is inactive)*/
#define TIMER_PWMMode_1										6U				/*When CNT<CCRx The channel is active (OCxREF = 1)
																											When CNT>CCRx	The channel is inactive (OCxREF =0)*/
#define TIMER_PWMMode_2										7U				/*When CNT<CCRx The channel is inactive (OCxREF = 0)
																											When CNT>CCRx	The channel is active (OCxREF =1)*/
																											
/**************/


/*define_TIMER_Polarity*/
#define TIMER_NoneInverted   					0U			/*Active on High Level or Rising Edge*/
#define TIMER_Inverted							1U			/*Active on Low Level or Falling Edge*/


/**************/


/*define_TIMER_ChannelPrescaler*/
#define TIMER_ChannelNoPrescaler		0U			/*Capture is done at each time an edge is detected on the channel*/
#define TIMER_ChannelPrescaler_2		1U			/*Capture is done once every 2 time an edge is detected on the channel*/
#define TIMER_ChannelPrescaler_4		2U			/*Capture is done once every 4 time an edge is detected on the channel*/
#define TIMER_ChannelPrescaler_8		3U			/*Capture is done once every 4 time an edge is detected on the channel*/


/**************/


/*define_TIMER_ChannelFillter*/
#define TIMER_NoFillter										0U				/*No fillter on Channel*/
#define TIMER_fckINT_2Event								1U				/*f_sampling = f_ck_INT and need 2 consecutive event to validate transition*/
#define TIMER_fckINT_4Event								2U				/*f_sampling = f_ck_INT and need 4 consecutive event to validate transition*/
#define TIMER_fckINT_8Event								3U				/*f_sampling = f_ck_INT and need 8 consecutive event to validate transition*/
#define TIMER_fckDTS_divide2_6Event				4U				/*f_sampling = f_ck_DTS/2 and need 6 consecutive event to validate transition*/
#define TIMER_fckDTS_divide2_8Event				5U				/*f_sampling = f_ck_DTS/2 and need 8 consecutive event to validate transition*/
#define TIMER_fckDTS_divide4_6Event				6U				/*f_sampling = f_ck_DTS/4 and need 6 consecutive event to validate transition*/
#define TIMER_fckDTS_divide4_8Event				7U				/*f_sampling = f_ck_DTS/4 and need 8 consecutive event to validate transition*/
#define TIMER_fckDTS_divide8_6Event				8U				/*f_sampling = f_ck_DTS/8 and need 6 consecutive event to validate transition*/
#define TIMER_fckDTS_divide8_8Event				9U				/*f_sampling = f_ck_DTS/8 and need 8 consecutive event to validate transition*/
#define TIMER_fckDTS_divide16_5Event			10U				/*f_sampling = f_ck_DTS/16 and need 5 consecutive event to validate transition*/
#define TIMER_fckDTS_divide16_6Event			11U				/*f_sampling = f_ck_DTS/16 and need 6 consecutive event to validate transition*/
#define TIMER_fckDTS_divide16_8Event			12U				/*f_sampling = f_ck_DTS/16 and need 8 consecutive event to validate transition*/
#define TIMER_fckDTS_divide32_5Event			13U				/*f_sampling = f_ck_DTS/32 and need 5 consecutive event to validate transition*/
#define TIMER_fckDTS_divide32_6Event			14U				/*f_sampling = f_ck_DTS/32 and need 6 consecutive event to validate transition*/
#define TIMER_fckDTS_divide32_8Event			15U				/*f_sampling = f_ck_DTS/32 and need 8 consecutive event to validate transition*/



/**************/


/*define_TIMER_Event*/
#define TIMER_UpdateEvent									0U			  /*Reinitialize the counter and load the value from ARR to shadow register if Auto Preload is enable
																										- If generation Bit UIF is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for all Timer*/
#define TIMER_ChannelEvent_1							1U				/*If Channel have been configured as input then capture the value in CNT register to CCR1 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR1
																										- If generation Bit CC1G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** NOT avaiable for TIM6 - TIM7*/
#define TIMER_ChannelEvent_2							2U				/*If Channel have been configured as input then capture the value in CNT register to CCR2 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR2
																										- If generation Bit CC2G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM12*/
#define TIMER_ChannelEvent_3							3U				/*If Channel have been configured as input then capture the value in CNT register to CCR3 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR3
																										- If generation Bit CC3G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8*/
#define TIMER_ChannelEvent_4							4U				/*If Channel have been configured as input then capture the value in CNT register to CCR4 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR4
																										- If generation Bit CC4G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8*/
#define TIMER_ChannelControlEvent					5U				/*Update CCxE,CCxNE,OCxM bit
																										- If generation Bit COMG is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM8*/
#define TIMER_TriggerEvent								6U				/*The counter start to count in some slave mode 
																										- If generation Bit TIF is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM12*/
#define TIMER_BreakEvent									7U				/*Break Mode
																										- If generation Bit BIF is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM8*/


/**************/


/*define_TIM_InterruptEvent*/
#define TIMER_UpdateInterrupt							0U			  /*Reinitialize the counter and load the value from ARR to shadow register if Auto Preload is enable
																										***** avaiable for all Timer*/
#define TIMER_ChannelInterrupt_1					1U				/*If Channel have been configured as input then capture the value in CNT register to CCR1 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR1
																										- If generation Bit CC1G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** NOT avaiable for TIM6 - TIM7*/
#define TIMER_ChannelInterrupt_2					2U				/*If Channel have been configured as input then capture the value in CNT register to CCR2 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR2
																										- If generation Bit CC2G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM12*/
#define TIMER_ChannelInterrupt_3					3U				/*If Channel have been configured as input then capture the value in CNT register to CCR3 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR3
																										- If generation Bit CC3G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8*/
#define TIMER_ChannelInterrupt_4					4U				/*If Channel have been configured as input then capture the value in CNT register to CCR4 register
																											If Channel have been configured as output then let image the channel 1 is forced  CNT = CCR4
																										- If generation Bit CC4G is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8*/
#define TIMER_ChannelControlInterrupt			5U				/*Update CCxE,CCxNE,OCxM bit
																										- If generation Bit COMG is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM8*/
#define TIMER_TriggerInterrupt						6U				/*The counter start to count in some slave mode 
																										- If generation Bit TIF is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM12*/
#define TIMER_BreakInterrupt							7U				/*Break Mode
																										- If generation Bit BIF is set in Timer Status Register - The interrupt or DMA can occur if enable
																										***** avaiable for TIM1 - TIM8*/				


/**************************************************************************/
/**************************************************************************/
/**************************************************************************/



TIM_Status TIM_ConfigureCounter(TIM_ConfigureCounterStruct *HTimer);
TIM_Status TIM_ConfigureControl(TIM_ConfigureControlStruct *HTimer);
TIM_Status TIM_ConfigureSlaveMode(TIM_ConfigureSlaveModeStruct *HTimer);
TIM_Status TIM_ConfigureChannel(TIM_ConfigureChannelStruct *HTimer);

TIM_Status TIM_EnableChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel);
TIM_Status TIM_DisableChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel);
TIM_Status TIM_EnableComplementaryChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel);
TIM_Status TIM_DisableComplementaryChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel);
TIM_Status TIM_EventGeneration(TIM_RegStruct *Timer,uint8_t TIMER_Event);

TIM_Status TIM_WriteAutoReloadValue(TIM_RegStruct *Timer,uint16_t TIMER_AutoReloadValue);
TIM_Status TIM_ReadAutoReloadValue(TIM_RegStruct *Timer,uint16_t* TIMER_AutoReloadValue);
TIM_Status TIM_WriteCountingValue(TIM_RegStruct *Timer,uint16_t TIMER_CountingValue);
TIM_Status TIM_ReadCountingValue(TIM_RegStruct *Timer,uint16_t* TIMER_CountingValue);
TIM_Status TIM_WritePrescalerValue(TIM_RegStruct *Timer,uint16_t TIMER_PrescalerValue);
TIM_Status TIM_ReadPrescalerValue(TIM_RegStruct *Timer,uint16_t* TIMER_PrescalerValue);
TIM_Status TIM_WriteChannelValue(TIM_RegStruct *Timer,uint8_t TIMER_Channel, uint16_t TIMER_ChannelValue);
TIM_Status TIM_ReadChannelValue(TIM_RegStruct *Timer,uint8_t TIMER_Channel, uint16_t *TIMER_ChannelValue);

TIM_Status TIM_ConfigureInterrupt(TIM_RegStruct *Timer,uint8_t TIM_InterruptEvent,uint8_t TIM_InterruptPriority,uint8_t TIM_IRQNumber);

void TIM1_BRK_IRQHandler(void);
void TIM1_UP_IRQHandler(void);
void TIM1_TRG_COM_IRQHandler(void);
void TIM1_CC_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void TIM4_IRQHandler(void);
#endif

