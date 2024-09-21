#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdint.h>



#define Motor_Drive_Direction_1								TIMER_Channel_1
#define Motor_Drive_Direction_2								TIMER_Channel_2
#define Motor_Drive_InverseDirection_1				TIMER_Channel_3
#define Motor_Drive_InverseDirection_2				TIMER_Channel_4


void Motor_Initialization(void);
void Motor_Configure_PWM(uint8_t Motor_Timer_Channel,uint8_t PWM_Percent);
#endif

