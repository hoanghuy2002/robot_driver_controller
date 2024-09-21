#ifndef _MOTOR_DRIVER_H_
#define _MOTOR_DRIVER_H_

#include <stdint.h>



void Robot_Stop();
void Robot_GoForward(uint8_t Speed_Percent);
void Robot_GoBackward(uint8_t Speed_Percent);
void Robot_TurnRight(uint8_t Speed_Percent);
void Robot_TurnLeft(uint8_t Speed_Percent);

#endif

