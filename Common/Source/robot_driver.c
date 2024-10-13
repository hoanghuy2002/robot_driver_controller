#include "robot_driver.h"
#include "motor_driver.h"

float Z_Axis_Zero_State = 0;


uint8_t Robot_Setup()
{
    Motor_Initialization();
	Motor_Timer_EnableCounter();
}


void Robot_Stop()
{
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_BackwardDirection_1_Channel,0);
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_BackwardDirection_2_Channel,0);
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_ForwardDirection_1_Channel,0);
	TIM_WriteChannelValue(Motor_Timer,Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_GoForward(int8_t Left_Speed_Percent,int8_t Right_Speed_Percent)
{
	if (Left_Speed_Percent < 0) Left_Speed_Percent = 0;
	if (Right_Speed_Percent < 0) Right_Speed_Percent = 0;
	
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,(uint8_t)(Left_Speed_Percent*25/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,(uint8_t)(Right_Speed_Percent*25/100));
}

void Robot_GoBackward(int8_t Left_Speed_Percent,int8_t Right_Speed_Percent)
{
	if (Left_Speed_Percent < 0) Left_Speed_Percent = 0;
	if (Right_Speed_Percent < 0) Right_Speed_Percent = 0;
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,(uint8_t)(Left_Speed_Percent*25/100));
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,(uint8_t)(Right_Speed_Percent*25/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_TurnRight(int8_t Speed_Percent)
{
	if (Speed_Percent < 0) Speed_Percent = 0;
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,(uint8_t)(Speed_Percent*25/100));
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,0);
}

void Robot_TurnLeft(int8_t Speed_Percent)
{
	if (Speed_Percent < 0) Speed_Percent = 0;
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_BackwardDirection_2_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_1_Channel,0);
	Motor_Configure_PWM(Motor_Drive_ForwardDirection_2_Channel,(uint8_t)(Speed_Percent*25/100));
}


