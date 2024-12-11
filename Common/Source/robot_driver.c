#include <stdlib.h>
#include "robot_driver.h"
#include "motor_driver.h"
#include "mpu6050_driver.h"
#include "rcc_driver.h"
#include "millisecond.h"
#include "ultrasonic.h"
#include "delay.h"
#include "serial_driver.h"
#include "string_handler.h"

#define Pi														3.1416
#define Radius_Of_Wheel											3.25		// 3.25cm.


uint8_t Robot_Setup()
{
	Delay_ms(1000);
    Motor_Initialization();
	Encoder_Initialization();
	MPU6050_Setup();
	Ultrasonic_Initialization();
    Ultrasonic_Trigger();
	MilliSecond_Setup();
}


/// Robot Movement Controller ///
void Robot_Stop()
{
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_GoForward(int8_t Speed_Percent)
{
	if (Speed_Percent < 0) Speed_Percent = 0;
	else if (Speed_Percent > 100) Speed_Percent =100;
	
	
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,(uint8_t)(Speed_Percent*70/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,(uint8_t)(Speed_Percent*69/100));
}

void Robot_GoBackward(int8_t Speed_Percent)
{
	if (Speed_Percent < 0) Speed_Percent = 0;
	else if (Speed_Percent > 100) Speed_Percent =100;


	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,(uint8_t)(Speed_Percent*70/100));
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,(uint8_t)(Speed_Percent*65/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_TurnRight(int8_t Speed_Percent)
{
	if (Speed_Percent < 0) Speed_Percent = 0;
	else if (Speed_Percent > 100) Speed_Percent = 100;
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,(uint8_t)(Speed_Percent));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_TurnLeft(int8_t Speed_Percent)
{
	if (Speed_Percent < 0) Speed_Percent = 0;
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,(uint8_t)(Speed_Percent));
}


/// Robot Encoder Controller (Measure Distance) 
void Robot_Start_Measure_Distance(void)
{
	Encoder_Reset();
	Encoder_Start();
}

float Robot_Get_Instantaneous_Distance(void)
{
 	float Number_Pulse = 0;
	Number_Pulse =(float) Encoder_Get_Value();
	float Instantaneous_Distance = 2*Pi*Radius_Of_Wheel*(Number_Pulse/Encoder_Pulses_Per_Revolution);
	Encoder_Reset();
	return Instantaneous_Distance;
}

void Robot_Stop_Measure_Distance(void)
{
	Encoder_Reset();
	Encoder_Stop();
}

/// Robot MPU6050 Controller (Measure Distance) 
void Robot_Start_Measure_Angle(void)
{
	MilliSecond_Start();
}

float Robot_Get_Instantaneous_Angle(void)
{
	volatile float Instantaneous_Angle = 0;
	volatile uint16_t Delta_Time = MilliSecond_Stop();
	MPU6050_Measure_Angle_Rotation(MPU6050_Z_Axis,Delta_Time/1000.0,&Instantaneous_Angle);
	MilliSecond_Start();
	return Instantaneous_Angle;
}

void Robot_Stop_Measure_Angle(void)
{
	MilliSecond_Stop();
}

uint8_t Robot_Detect_Object(void)
{
	uint8_t Is_Detected_Object =0;
	float Center_Distance = Ultrasonic_Get_Distance(Ultrasonic_Center);
	float Left_Distance = Ultrasonic_Get_Distance(Ultrasonic_Left);
	float Right_Distance = Ultrasonic_Get_Distance(Ultrasonic_Right);
	if (Left_Distance < 5 || Right_Distance < 5 || Center_Distance < 7)
	{
		Is_Detected_Object = 1;
	}

	return Is_Detected_Object;
}	




