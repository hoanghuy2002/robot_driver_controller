#ifndef _ROBOT_DRIVER_H_
#define _ROBOT_DRIVER_H_
#include <stdint.h>

uint8_t Robot_Setup();
void Robot_Stop(void);
void Robot_GoForward(uint8_t Left_Speed_Percent,uint8_t Right_Speed_Percent);
void Robot_GoBackward(uint8_t Left_Speed_Percent,uint8_t Right_Speed_Percent);
void Robot_TurnRight(uint8_t Speed_Percent);
void Robot_TurnLeft(uint8_t Speed_Percent);

#endif