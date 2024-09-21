#include "timer_driver.h"
#include "cortexm3_irq.h"

/*********************************************************************
 * @fn      		  		- TIM_ConfigureCounter
 *
 * @brief             - This function to Configure Basic Counter of Timer
 *
 * @param[1]          - Address of local structure TIM_ConfigureCounterStruct
 *
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 *											 TIM_Error: If The Timer's Counter is counting
 * 											 TIM_Success: If configure success but not guarantee to specific timer have particular parameter (e.g. Timer 6 dont configure TIMER_DirectionMode parameter) 
 *
 * @Note              -  Please check all the referrence to structure's members in filer timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer (e.g. if you configure counter for timer 6, you will not configure TIMER_DirectionMode 
												 because timer 6 does not have this feature. If you configure the function also return TIM_Success but the timer's counter will not 
												 running like your direction you configure)

 */
 
TIM_Status TIM_ConfigureCounter(TIM_ConfigureCounterStruct *HTimer)
{
	/*Check Did Timer is busy?*/
	uint32_t Temp = HTimer->Timer->CR1;
	if((Temp &= 0x01) == 1)
	{
		return TIM_Error;
	}
	/*Check Parameter*/
	if(HTimer->Timer == TIM1 || HTimer->Timer == TIM2 || HTimer->Timer == TIM3 || HTimer->Timer == TIM4 || HTimer->Timer == TIM5 || HTimer->Timer == TIM6
	|| HTimer->Timer == TIM7 || HTimer->Timer == TIM8 || HTimer->Timer == TIM9 || HTimer->Timer == TIM10 || HTimer->Timer == TIM11 || HTimer->Timer == TIM12
	|| HTimer->Timer == TIM13 || HTimer->Timer == TIM14)
	{
		if((HTimer->TIMER_AutoReloadPreload > 1) || ((HTimer->TIMER_DirectionMode == 4 || HTimer->TIMER_DirectionMode == 6) || HTimer->TIMER_DirectionMode>7))
			return TIM_ParameterError;
		if(((HTimer->Timer != TIM1) && (HTimer->Timer != TIM8)) && (HTimer->TIMER_RepetitionCounter !=0))
			return TIM_ParameterError;
		if (((HTimer->Timer == TIM6) || (HTimer->Timer == TIM7 || (HTimer->Timer == TIM9) ) || (HTimer->Timer == TIM10) 
			 ||(HTimer->Timer == TIM11) || (HTimer->Timer == TIM11) || (HTimer ->Timer == TIM12) || (HTimer->Timer == TIM13)
		   ||(HTimer->Timer == TIM14))&& (HTimer->TIMER_DirectionMode != 0))
			return TIM_ParameterError;
		if (HTimer->TIMER_DirectionMode ==0)
			HTimer->TIMER_DirectionMode =1;
		/*Reset Necessary Bits in Registers*/
		HTimer->Timer->CR1 &= 0xFF0F;
		HTimer->Timer->CR1 |= (uint32_t)(HTimer->TIMER_AutoReloadPreload<<7 | (HTimer->TIMER_DirectionMode-1)<<4);
		HTimer->Timer->PSC = HTimer->TIMER_PreScaler;
		HTimer->Timer->CNT = HTimer->TIMER_Counter;
		HTimer->Timer->RCR = HTimer->TIMER_RepetitionCounter;
		HTimer->Timer->ARR = HTimer->TIMER_AutoReload;
		return TIM_Success;
	}
	else return TIM_ParameterError;
}


/*********************************************************************
 * @fn      		  		- TIM_ConfigureControl
 *
 * @brief             - This function to Configure Basic Control of Timer
 *
 * @param[1]          - Address of local structure TIM_ConfigureControlStruct
 *
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 *											 TIM_Error: If The Timer's Counter is counting
 * 											 TIM_Success: If configure success but not guarantee to specific timer have particular parameter.
 *
 * @Note              -  Please check all the referrence to structure's members in filer timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer (If you configure the the feature timer does not have, this function also return TIM_Success 
												 but the timer will not running this feature)

 */

TIM_Status TIM_ConfigureControl(TIM_ConfigureControlStruct *HTimer)
{
	/*Check Did Timer is busy?*/
	uint32_t Temp = HTimer->Timer->CR1;
	if((Temp &= 0x01) == 1)
	{
		return TIM_Error;
	}
	/*Check Parameter*/
	if(HTimer->Timer == TIM1 || HTimer->Timer == TIM2 || HTimer->Timer == TIM3 || HTimer->Timer == TIM4 || HTimer->Timer == TIM5 || HTimer->Timer == TIM6
	|| HTimer->Timer == TIM7 || HTimer->Timer == TIM8 || HTimer->Timer == TIM9 || HTimer->Timer == TIM10 || HTimer->Timer == TIM11 || HTimer->Timer == TIM12
	|| HTimer->Timer == TIM13 || HTimer->Timer == TIM14)
	{
		if((HTimer->TIMER_ClockDivision >2) || (HTimer->TIMER_UpdateEventControl >1) || (HTimer->TIMER_UIF_RequestSource >1) || (HTimer->TIMER_OnePulseMode >1)
		|| (HTimer->TIMER_TI1_Selection>1) || (HTimer->TIMER_MasterMode > 7))
		{
			return TIM_ParameterError;
		}
		/*Reset necessary Bits in Registers*/
		HTimer->Timer->CR1 &= 0x00F1;						/*Reset Bits CKD - OPM - URS - UDIS in Timer's CR1 Register*/
		HTimer->Timer->CR2 &= 0xFF0F;						/*Reset Bits TI1S - MMS in Timer's CR2 Register*/
		/*Configure CR1 register and CR2 register*/ 
		HTimer->Timer->CR1 |= (uint32_t)((HTimer->TIMER_ClockDivision<<8)|(HTimer->TIMER_OnePulseMode<<3)
																		|(HTimer->TIMER_UIF_RequestSource<<2)|((!HTimer->TIMER_UpdateEventControl)<<1));
		HTimer->Timer->CR2 |= (uint32_t)((HTimer->TIMER_TI1_Selection<<7)|(HTimer->TIMER_MasterMode<<4));
		return TIM_Success;
	}
	else return TIM_ParameterError;
}


/*********************************************************************
 * @fn      		  		-  TIM_ConfigureSlaveMode
 *
 * @brief             -  This function to Configure Slave Mode of Timer
 * @param[1]          -  Address of local structure TIM_ConfigureSlaveModeStruct
 *
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 *											 TIM_Error: If The Timer's Counter is counting
 * 											 TIM_Success: If configure success but not guarantee to specific timer have particular parameter (Read Note to understading).
 *
 * @Note              -  Please check all the referrence to structure's members in filer timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer (If you configure the the feature timer does not have, this function also return TIM_Success 
												 but the timer will not running this feature)

 */


TIM_Status TIM_ConfigureSlaveMode(TIM_ConfigureSlaveModeStruct *HTimer)
{
	/*Check Did Timer is busy?*/
	uint32_t Temp = HTimer->Timer->CR1;
	if((Temp &= 0x01) == 1)
	{
		return TIM_Error;
	}
	/*Check Parameter*/
	if(HTimer->Timer == TIM1 || HTimer->Timer == TIM2 || HTimer->Timer == TIM3 || HTimer->Timer == TIM4 
	 ||HTimer->Timer == TIM5 || HTimer->Timer == TIM8 || HTimer->Timer == TIM9 || HTimer->Timer == TIM12)
	{
		if(HTimer->TIMER_SlaveMode > 7 || HTimer->TIMER_TriggerInput > 7 || HTimer->TIMER_ExternalClockMode_2 > 1 || HTimer->TIMER_ExternalTriggerPolarity > 1
		 ||HTimer->TIMER_ExternalTriggerPrescaler > 3 || HTimer->TIMER_ExternalTriggerPolarity > 15)
		{
			return TIM_ParameterError;
		}
		/*Reset Slave Mode Control Register except MMS bit*/
		HTimer->Timer->SMCR &= (uint32_t)(1<<7);
		HTimer->Timer->SMCR |= (uint32_t)(HTimer->TIMER_SlaveMode<<0 | HTimer->TIMER_TriggerInput<<4 | HTimer->TIMER_ExternalTriggerFillter<<8 
																		| HTimer->TIMER_ExternalTriggerPrescaler<<12 | HTimer->TIMER_ExternalClockMode_2<<14 
																		| HTimer->TIMER_ExternalTriggerPolarity<<15);
		return TIM_Success;
	}
	else return TIM_ParameterError;
}


/*********************************************************************
 * @fn      		  		-  TIM_ConfigureChannel
 *
 * @brief             -  This function to Configure Channel of Timer, also configure mode of channel (Input capture mode or output compare mode)
												 This feature doesn't support for TIM6 and TIM7
 * @param[1]          -  Address of local structure TIM_ConfigureChannelStruct
 *
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 *											 TIM_Error: If The Timer's Counter is counting
 * 											 TIM_Success: If configure success but not guarantee to specific timer have particular parameter (Read Note to understading).
 *
 * @Note              -  Please check all the referrence to structure's members in filer timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer (If you configure the the feature timer does not have, this function also return TIM_Success 
												 but the timer will not running this feature)

 */

TIM_Status TIM_ConfigureChannel(TIM_ConfigureChannelStruct *HTimer)
{
	/*Check Did Timer is busy?*/
	uint32_t Temp = HTimer->Timer->CR1;
	if((Temp &= 0x01) == 1)
	{
		return TIM_Error;
	}
	/*Check Parameter*/
	if(HTimer->Timer == TIM1 || HTimer->Timer == TIM2 || HTimer->Timer == TIM3 || HTimer->Timer == TIM4 ||HTimer->Timer == TIM5 
	|| HTimer->Timer == TIM8 || HTimer->Timer == TIM9 || HTimer->Timer == TIM10 || HTimer->Timer == TIM11 ||HTimer->Timer == TIM12
	|| HTimer->Timer == TIM13 || HTimer->Timer == TIM14)
	{
		if(HTimer->TIMER_Channel>>3 || HTimer->TIMER_ChannelDirection>3 || HTimer->TIMER_ChannelPolarity>1 || HTimer->TIMER_ComplementaryChannelPolarity >1
		 ||HTimer->TIMER_InputCapturePrescaler>3 || HTimer->TIMER_InputCaptureFillter>15 || HTimer->TIMER_OutputCompareFast >1 
		 ||HTimer->TIMER_OutputComparePreload>1 || HTimer->TIMER_OutputCompareMode>7 || HTimer->TIMER_OutputCompareClear >1)
		{
			return TIM_ParameterError;
		}
		/*Reset polarity of channel and complementary channel in capture/compare enable register (CCER)*/
		HTimer->Timer->CCER &= ~(uint32_t)(1<<(1+HTimer->TIMER_Channel*4) | 1<<(3+HTimer->TIMER_Channel*4));
		/*Configure polarity for channel and complementary channel*/
		HTimer->Timer->CCER |= (uint32_t) (HTimer->TIMER_ChannelPolarity<<(1+HTimer->TIMER_Channel*4) 
																		  |HTimer->TIMER_ComplementaryChannelPolarity<<(3+HTimer->TIMER_Channel*4));
		
		/*Find the CCMRx to configure depend on Channel 
		e.g (If channel 1 or channel2 then will configure on CCMR1) and (If channel 3 or channel 4 then will configure on CCMR2)*/
		if(HTimer->TIMER_Channel < 2)
		{
			/*Reset 8 bit configure channel base on Channel to configure correct feature from user
			e.g if Channel 1 or Channel 3 then will be reset 8 bit LSB in CCMR1 or CCMR2
					if channel 2 or channel 4 then will be reset 8 bit from bit 7 to bit 15 in CCMR1 or CCMR2*/
			HTimer->Timer->CCMR1 &= ~(uint32_t)(0xFF<<(8*HTimer->TIMER_Channel));
			/*Confifure the feature have been selected from application*/
			if(HTimer->TIMER_ChannelDirection == TIMER_OutputChannel)
			{
				Temp = (uint32_t)(HTimer->TIMER_OutputCompareFast<<2 | HTimer->TIMER_OutputComparePreload<<3 
												 |HTimer->TIMER_OutputCompareMode<<4 | HTimer->TIMER_OutputCompareClear<<7);
			}
			else
			{
				Temp = (uint32_t)(HTimer->TIMER_InputCapturePrescaler<<2 | HTimer->TIMER_InputCaptureFillter<<4);
			}
			HTimer->Timer->CCMR1 |= (uint32_t)(HTimer->TIMER_ChannelDirection<<(8*HTimer->TIMER_Channel));
			HTimer->Timer->CCMR1 |= (uint32_t)(Temp<<(8*HTimer->TIMER_Channel));
		}
		else
		{
			/*Reset 8 bit configure channel base on Channel to configure correct feature from user
			e.g if Channel 1 or Channel 3 then will be reset 8 bit LSB in CCMR1 or CCMR2
					if channel 2 or channel 4 then will be reset 8 bit from bit 7 to bit 15 in CCMR1 or CCMR2*/
			HTimer->Timer->CCMR2 &= ~(uint32_t)(0xFF<<(8*(HTimer->TIMER_Channel-2)));
			/*Confifure the feature have been selected from application*/
			if(HTimer->TIMER_ChannelDirection == TIMER_OutputChannel)
			{
				Temp = (uint32_t)(HTimer->TIMER_OutputCompareFast<<2 | HTimer->TIMER_OutputComparePreload<<3 
												 |HTimer->TIMER_OutputCompareMode<<4 | HTimer->TIMER_OutputCompareClear<<7);
			}
			else
			{
				Temp = (uint32_t)(HTimer->TIMER_InputCapturePrescaler<<2 | HTimer->TIMER_InputCaptureFillter<<4);
			}
			HTimer->Timer->CCMR2 |= (uint32_t)(HTimer->TIMER_ChannelDirection<<(8*(HTimer->TIMER_Channel-2)));
			HTimer->Timer->CCMR2 |= (uint32_t)(Temp<<(8*(HTimer->TIMER_Channel-2)));
		}
		if((HTimer->Timer == TIM1 || HTimer->Timer == TIM8) && HTimer->TIMER_ChannelDirection == TIMER_OutputChannel)
		{
			HTimer->Timer->BDTR |= 1<<15;					/*Enable Main output enable for TIM1 and TIM8 if configure as Output*/
		}
		HTimer->Timer->CCER |= (1<<4*HTimer->TIMER_Channel);			/*Enable Channel*/
		return TIM_Success;
	}
	else return TIM_ParameterError;
}



/*********************************************************************
 * @fn      		  		-  TIM_EnableChannel
 *
 * @brief             -  This function to Enable Channel so as to the channel start with the  feature mode have been configure
 * @param[1]          -  Specific Timer:avaiable for  TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM10 - TIM11 - TIM12 - TIM13 - TIM14
 * @param[2]          -  Specific Timer Channel: @ref define_TIMER_Channel in file timer_driver.h
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If configure success.
 *
 * @Note              -  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */




TIM_Status TIM_EnableChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM2 || Timer==TIM3 || Timer==TIM4 || Timer==TIM5 || Timer==TIM8)
	{
		if(TIMER_Channel>3) return TIM_ParameterError;
	}
	else if(Timer==TIM9 || Timer==TIM12)
	{
		if(TIMER_Channel>1) return TIM_ParameterError;
	}
	else if(Timer==TIM10 || Timer==TIM11 || Timer==TIM13 || Timer==TIM14)
	{
		if(TIMER_Channel>0) return TIM_ParameterError;
	}
	else return TIM_ParameterError;
	Timer->CCER |= (1<<4*TIMER_Channel);
	return TIM_Success;
}


/*********************************************************************
 * @fn      		  		-  TIM_DisableChannel
 *
 * @brief             -  This function to Disable Channel so as to stop the channel
 * @param[1]          -  Specific Timer: avaiablefor TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM10 - TIM11 - TIM12 - TIM13 - TIM14
 * @param[2]          -  Specific Timer Channel: @ref define_TIMER_Channel in file timer_driver.h
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If configure success.
 *
 * @Note              -  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_DisableChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM2 || Timer==TIM3 || Timer==TIM4 || Timer==TIM5 || Timer==TIM8)
	{
		if(TIMER_Channel>3) return TIM_ParameterError;
	}
	else if(Timer==TIM9 || Timer==TIM12)
	{
		if(TIMER_Channel>1) return TIM_ParameterError;
	}
	else if(Timer==TIM10 || Timer==TIM11 || Timer==TIM13 || Timer==TIM14)
	{
		if(TIMER_Channel>0) return TIM_ParameterError;
	}
	else return TIM_ParameterError;
	Timer->CCER &= ~(uint32_t)(1<<4*TIMER_Channel);
	return TIM_Success;
}



/*********************************************************************
 * @fn      		  		-  TIM_EnableComplementaryChannel
 *
 * @brief             -  This function to Enable Channel so as to the complementary channel start with the  feature mode have been configure
 * @param[1]          -  Specific Timer: avaiable for TIM1 - TIM8
 * @param[2]          -  Specific Timer Channel: @ref define_TIMER_Channel in file timer_driver.h
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If configure success.
 *
 * @Note              -  Please check all the referrence of parameter in filer timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */


TIM_Status TIM_EnableComplementaryChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM8)
	{
		if(TIMER_Channel>3) return TIM_ParameterError;
	}
	else return TIM_ParameterError;
	Timer->CCER |= (1<<(2+4*TIMER_Channel));
	return TIM_Success;
}



/*********************************************************************
 * @fn      		  		-  TIM_DisableComplementaryChannel
 *
 * @brief             -  This function to Disable Complementary Channel so as to stop the feature of complementary channel
 * @param[1]          -  Specific Timer: avaiable for TIM1 - TIM8
 * @param[2]          -  Specific Timer Channel: @ref define_TIMER_Channel in file timer_driver.h
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If configure success.
 *
 * @Note              -  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */


TIM_Status TIM_DisableComplementaryChannel(TIM_RegStruct *Timer, uint8_t TIMER_Channel)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM8)
	{
		if(TIMER_Channel>3) return TIM_ParameterError;
	}
	else return TIM_ParameterError;
	Timer->CCER &= ~(uint32_t)(1<<(2+4*TIMER_Channel));
	return TIM_Success;
}



/*********************************************************************
 * @fn      		  		-  TIM_EventGeneration
 *
 * @brief             -  This function to generation suitable event have been selected
 * @param[1]          -  Specific Timer: avaiable for all Timer
 * @param[2]          -  Specific Timer Event to be generate: @ref define_TIMER_Event in file timer_driver.h
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If configure success.
 *
 * @Note              -  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_EventGeneration(TIM_RegStruct *Timer,uint8_t TIMER_Event)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM8)
	{
		if(TIMER_Event >7) return TIM_ParameterError;
	}
	else if(Timer==TIM2 || Timer==TIM3 || Timer==TIM4 || Timer==TIM5)
	{
		if(TIMER_Event == 5 || TIMER_Event >7) return TIM_ParameterError;
	}
	else if(Timer==TIM9 || Timer==TIM12)
	{
		if(TIMER_Event>2 && TIMER_Event != 6) return TIM_ParameterError;
	}
	else if(Timer==TIM10 || Timer==TIM11 || Timer==TIM13 || Timer==TIM14)
	{
		if(TIMER_Event>1) return TIM_ParameterError;
	}
	else
	{
		if(TIMER_Event>0) return TIM_ParameterError;
	}
	Timer->EGR |= (uint32_t)(1<<TIMER_Event);
	return TIM_Success;
}


/*********************************************************************
 * @fn      		  		-  TIM_WriteAutoReloadValue
 *
 * @brief             -  This function to Write value to ARR register use to reinitialize when CNT = ARR
 * @param[1]          -  Specific Timer:avaiable for  all Timer
 * @param[2]          -  Specific TIMER_AutoReloadValue: the value use to reinitialize when Counter count to this value. the value between 0 and 0xFFFF
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Write success.
 *
 * @Note              -  This function only use if channel have been configure as output
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */


TIM_Status TIM_WriteAutoReloadValue(TIM_RegStruct *Timer,uint16_t TIMER_AutoReloadValue)
{
	Timer->ARR = TIMER_AutoReloadValue;
	return TIM_Success;
}



/*********************************************************************
 * @fn      		  		-  TIM_ReadAutoReloadValue
 *
 * @brief             -  This function use to read the content of the ARR register
 * @param[1]          -  Specific Timer:avaiable for  all Timer
 * @param[2]          -  Specific *TIMER_AutoReloadValue: the adrress of variable contain the value reading
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Read success.
 *
 * @Note              -  This function only use if channel have been configure as output
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */



TIM_Status TIM_ReadAutoReloadValue(TIM_RegStruct *Timer,uint16_t* TIMER_AutoReloadValue)
{
	*TIMER_AutoReloadValue =(uint16_t) Timer->ARR;
	return TIM_Success;
}




/*********************************************************************
 * @fn      		  		-  TIM_WriteCountingValue
 *
 * @brief             -  This function to Write value to CNT register.
 * @param[1]          -  Specific Timer:avaiable for  all Timer
 * @param[2]          -  Specific TIMER_CountingValue: the value use of CNT register
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Write success.
 *
 * @Note              -  This function only use if channel have been configure as output
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_WriteCountingValue(TIM_RegStruct *Timer,uint16_t TIMER_CountingValue)
{
	Timer->CNT = TIMER_CountingValue;
	return TIM_Success;
}



/*********************************************************************
 * @fn      		  		-  TIM_ReadCountingValue
 *
 * @brief             -  This function use to read the content of the CNT register
 * @param[1]          -  Specific Timer:avaiable for  all Timer
 * @param[2]          -  Specific *TIMER_CountingValue: the adrress of variable contain the value reading
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Read success.
 *
 * @Note              -  This function only use if channel have been configure as output
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_ReadCountingValue(TIM_RegStruct *Timer,uint16_t* TIMER_CountingValue)
{
	*TIMER_CountingValue =(uint16_t) Timer->CNT;
	return TIM_Success;
}


/*********************************************************************
 * @fn      		  		-  TIM_WritePrescalerValue
 *
 * @brief             -  This function use to Write value to PSC register to divide frequency input clock.
 * @param[1]          -  Specific Timer:avaiable for  all Timer
 * @param[2]          -  Specific TIMER_CountingValue: the value use of PSC register
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Write success.
 *
 * @Note              -  This function only use if channel have been configure as output
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_WritePrescalerValue(TIM_RegStruct *Timer,uint16_t TIMER_PrescalerValue)
{
	Timer->PSC = TIMER_PrescalerValue;
	return TIM_Success;
}



/*********************************************************************
 * @fn      		  		-  TIM_ReadPrescalerValue
 *
 * @brief             -  This function use to read the content of the PSC register
 * @param[1]          -  Specific Timer:avaiable for  all Timer
 * @param[2]          -  Specific *TIMER_PrescalerValue: the adrress of variable contain the value reading
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Read success.
 *
 * @Note              -  This function only use if channel have been configure as output
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_ReadPrescalerValue(TIM_RegStruct *Timer,uint16_t* TIMER_PrescalerValue)
{
	*TIMER_PrescalerValue =(uint16_t) Timer->PSC;
	return TIM_Success;
}




/*********************************************************************
 * @fn      		  		-  TIM_WriteChannelValue
 *
 * @brief             -  This function to Write value to CCRx register use to compare with CNT register in output compare mode
 * @param[1]          -  Specific Timer:avaiable for  TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM10 - TIM11 - TIM12 - TIM13 - TIM14
 * @param[2]          -  Specific TIMER_Channel: @ref define_TIMER_Channel in file timer_driver.h
 * @param[3]          -  Specific TIMER_ChannelValue: the value use to compare with CNT register in output compare mode. The value between 0 and 0xFFFF
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Write success.
 *
 * @Note              -  This function only use if channel have been configure as output
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_WriteChannelValue(TIM_RegStruct *Timer,uint8_t TIMER_Channel, uint16_t TIMER_ChannelValue)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM2 || Timer==TIM3 || Timer==TIM4 || Timer==TIM5 || Timer==TIM8)
	{
		if(TIMER_Channel>3) return TIM_ParameterError;
	}
	else if(Timer==TIM9 || Timer==TIM12)
	{
		if(TIMER_Channel>1) return TIM_ParameterError;
	}
	else if(Timer==TIM10 || Timer==TIM11 || Timer==TIM13 || Timer==TIM14)
	{
		if(TIMER_Channel>0) return TIM_ParameterError;
	}
	else return TIM_ParameterError;
	volatile uint32_t *Pointer;
	Pointer = &Timer->CCR1+1*TIMER_Channel;
	*Pointer = TIMER_ChannelValue;
	return TIM_Success;
}


/*********************************************************************
 * @fn      		  		-  TIM_ReadChannelValue
 *
 * @brief             -  This function to Read value from CCRx register in input compare mode
 * @param[1]          -  Specific Timer:avaiable for  TIM1 - TIM2 - TIM3 - TIM4 - TIM5 - TIM8 - TIM9 - TIM10 - TIM11 - TIM12 
																				- TIM13 - TIM14
 * @param[2]          -  Specific TIMER_Channel: @ref define_TIMER_Channel in file timer_driver.h
 * @param[3]          -  Specific *TIMER_ChannelValue:Address variable contain TIMER Channel's value in CCRx register. 
																	The value will between 0 and 0xFFFF. 
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Read success.
 *
 * @Note              -  This function only use if channel have been configure as input
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter you configure 
												 are avaiable for specific timer if not the return is TIM_ParameterError.

 */

TIM_Status TIM_ReadChannelValue(TIM_RegStruct *Timer,uint8_t TIMER_Channel, uint16_t *TIMER_ChannelValue)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM2 || Timer==TIM3 || Timer==TIM4 || Timer==TIM5 || Timer==TIM8)
	{
		if(TIMER_Channel>3) return TIM_ParameterError;
	}
	else if(Timer==TIM9 || Timer==TIM12)
	{
		if(TIMER_Channel>1) return TIM_ParameterError;
	}
	else if(Timer==TIM10 || Timer==TIM11 || Timer==TIM13 || Timer==TIM14)
	{
		if(TIMER_Channel>0) return TIM_ParameterError;
	}
	else return TIM_ParameterError;
	volatile uint32_t *Pointer;
	Pointer = &Timer->CCR1+1*TIMER_Channel;
	*TIMER_ChannelValue =(uint16_t)*Pointer;
	return TIM_Success;
}



/*********************************************************************
 * @fn      		  		-  TIM_ConfigureInterrupt
 *
 * @brief             -  This function use to Configure timer interrupt
 * @param[1]          -  Specific Timer:avaiable for all timer
 * @param[2]          -  Specific TIM_AdvancedEvent:Event lead to interrupt @ref define_TIM_InterruptEvent in file timer_driver.h
 * @param[3]          -  Specific TIM_InterruptPriority:Prority Interrupt configure 
 * @param[4]					-  Specific TIM_IRQNumber: @ref define_IRQNumber in file cortexm3.h
 * @return            -  TIM_ParameterError: If The parameter is not suitable
 * 											 TIM_Success: If Read success.
 *
 * @Note              -  This function only use if channel have been configure as input
											-  Please check all the referrence of parameter in file timer_driver.h and make sure all the parameter 
												 you configure are avaiable for specific timer if not the return is TIM_ParameterError.
												 Make sure Timer and TIM_IRQNumber is suitable.

 */

TIM_Status TIM_ConfigureInterrupt(TIM_RegStruct *Timer,uint8_t TIM_InterruptEvent,uint8_t TIM_InterruptPriority,uint8_t TIM_IRQNumber)
{
	/*Check suitable parameter*/
	if(Timer==TIM1 || Timer==TIM8)
	{
		if(TIM_InterruptEvent >7) return TIM_ParameterError;
	}
	else if(Timer==TIM2 || Timer==TIM3 || Timer==TIM4 || Timer==TIM5)
	{
		if(TIM_InterruptEvent == 5 || TIM_InterruptEvent >7) return TIM_ParameterError;
	}
	else if(Timer==TIM9 || Timer==TIM12)
	{
		if(TIM_InterruptEvent>2 && TIM_InterruptEvent != 6) return TIM_ParameterError;
	}
	else if(Timer==TIM10 || Timer==TIM11 || Timer==TIM13 || Timer==TIM14)
	{
		if(TIM_InterruptEvent>1) return TIM_ParameterError;
	}
	else
	{
		if(TIM_InterruptEvent>0) return TIM_ParameterError;
	}
	Timer->DIER |= (uint32_t)(1<<TIM_InterruptEvent);
	NVIC_Enable_IRQ(TIM_IRQNumber);
	NVIC_SetPriority_IRQ(TIM_IRQNumber,TIM_InterruptPriority);
	return TIM_Success;
}
