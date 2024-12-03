#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdint.h>
#include "timer_driver.h"

#define Motor_Timer												TIM2

#define Motor_Drive_ForwardDirection_1_Channel					TIMER_Channel_1
#define Motor_Drive_ForwardDirection_2_Channel					TIMER_Channel_2
#define Motor_Drive_BackwardDirection_1_Channel                 TIMER_Channel_3
#define Motor_Drive_BackwardDirection_2_Channel                 TIMER_Channel_4

#define	Motor_Timer_EnableCounter()								TIM2_EnableCounter()
#define Motor_Timer_DisableCounter()							TIM2_DisableCounter()	

///////////////////////////////
#define Encoder_Timer                                           TIM1

#define	Encoder_Timer_EnableCounter()							TIM1_EnableCounter()
#define Encoder_Timer_DisableCounter()							TIM1_DisableCounter()	

#define Encoder_Pulses_Per_Revolution                           495u

#define Encoder_Start()											Encoder_Timer_EnableCounter()
#define Encoder_Stop()											Encoder_Timer_DisableCounter()
#define Encoder_Reset()                                         TIM_WriteCountingValue(Encoder_Timer,0)

void Motor_Initialization(void);
void Motor_Configure_PWM(uint8_t Motor_Timer_Channel,uint8_t PWM_Percent);
void Encoder_Initialization(void);
uint16_t Encoder_Get_Value(void);

#endif

