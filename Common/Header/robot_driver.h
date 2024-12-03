#ifndef _ROBOT_DRIVER_H_
#define _ROBOT_DRIVER_H_
#include <stdint.h>


uint8_t Robot_Setup();
// Robot  
void Robot_Stop(void);
void Robot_GoForward(int8_t Left_Speed_Percent,int8_t Right_Speed_Percent);
void Robot_GoBackward(int8_t Left_Speed_Percent,int8_t Right_Speed_Percent);
void Robot_TurnRight(int8_t Speed_Percent);
void Robot_TurnLeft(int8_t Speed_Percent);

/// Robot Encoder Controller (Measure Distance) 
void Robot_Start_Measure_Distance(void);
float Robot_Get_Instantaneous_Distance(void);
void Robot_Stop_Measure_Distance(void);

/// Robot MPU6050 Controller (Measure Distance) 
void Robot_Start_Measure_Angle(void);
float Robot_Get_Instantaneous_Angle(void);
void Robot_Stop_Measure_Angle(void);

#endif