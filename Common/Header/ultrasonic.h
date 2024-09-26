#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_
#include <stdint.h>
#include "timer_driver.h"

#define Ultrasonic_Left											    TIMER_Channel_1
#define Ultrasonic_Center											TIMER_Channel_2
#define Ultrasonic_Right											TIMER_Channel_3
#define Ultrasonic_Trigger_Channel                                  TIMER_Channel_4

void Ultrasonic_Initialization(void);
void Ultrasonic_Trigger(void);
float Ultrasonic_Get_Distance(uint8_t Ultrasonic_Channel);
#endif

