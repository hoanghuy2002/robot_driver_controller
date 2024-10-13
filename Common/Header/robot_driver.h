#ifndef _ROBOT_DRIVER_H_
#define _ROBOT_DRIVER_H_
#include <stdint.h>

uint8_t Robot_Setup();
void Robot_Stop(void);
void Robot_GoForward(int8_t Left_Speed_Percent,int8_t Right_Speed_Percent);
void Robot_GoBackward(int8_t Left_Speed_Percent,int8_t Right_Speed_Percent);
void Robot_TurnRight(int8_t Speed_Percent);
void Robot_TurnLeft(int8_t Speed_Percent);

#endif