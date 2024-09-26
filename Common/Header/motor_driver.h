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

void Motor_Initialization(void);
void Motor_Configure_PWM(uint8_t Motor_Timer_Channel,uint8_t PWM_Percent);

#endif

