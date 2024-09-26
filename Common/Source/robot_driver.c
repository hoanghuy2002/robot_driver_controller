#include "robot_driver.h"
#include "motor_driver.h"

float Z_Axis_Zero_State = 0;


uint8_t Robot_Setup()
{
    Motor_Initialization();
    MilliSecond_Setup();
    MPU6050_Setup();
}


void Robot_Stop()
{
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_BackwardDirection_1_Channel,0);
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_BackwardDirection_2_Channel,0);
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_ForwardDirection_1_Channel,0);
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_GoForward(uint8_t Speed_Percent)
{
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,(uint8_t)(Speed_Percent*70/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,(uint8_t)(Speed_Percent*70/100));
}

void Robot_GoBackward(uint8_t Speed_Percent)
{
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,(uint8_t)(Speed_Percent*70/100));
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,(uint8_t)(Speed_Percent*70/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_TurnRight(uint8_t Speed_Percent)
{
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,(uint8_t)(Speed_Percent*70/100));
}

void Robot_TurnLeft(uint8_t Speed_Percent)
{

	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,(uint8_t)(Speed_Percent*70/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,0);
}


