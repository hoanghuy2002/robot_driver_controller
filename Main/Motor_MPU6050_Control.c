#include <stdio.h>
#include "rtos.h"
#include "robot_driver.h"
#include "millisecond.h"
#include "ultrasonic.h"
#include "rcc_driver.h"
#include "mpu6050_driver.h"
#include "gpio_driver.h"
#include "delay.h"
#include "cortexm3_irq.h"
#include <stdlib.h>


#define Kp                  0.5
#define Ki                  0.1
#define Kd                  0.05
#define PID_Delta_Time      0.05

#define Robot_Stop_Flag             0
#define Robot_BackWard_Flag         -1
#define Robot_ForWard_Flag          1
#define Robot_TurnLeft_Flag         2
#define Robot_TurnRight_Flag        3




int8_t Robot_Movement_Flag = Robot_TurnRight_Flag;
volatile int16_t Robot_Angle_Target = 90;
volatile float Robot_PID_Result = 0;
float Left_Distance,Center_Distance,Right_Distance = 0;


static void PID_Task(void)
{
    volatile float Error_Before = 0;
    volatile float Error_Total = 0;
    while ((1))
    {
        volatile float Error =(float)(0 - Robot_Angle_Target);
        Robot_PID_Result = Error*Kp + (Error-Error_Before)*Kd/PID_Delta_Time + Error_Total*Ki*PID_Delta_Time;
        if (Robot_PID_Result>100) Robot_PID_Result = 100;
        else if (Robot_PID_Result<-100) Robot_PID_Result = -100;
        RTOS_Delay_Task(50/Task_TickMiliSecond);
    }
    
}

static void Ultrasonic_Task(void)
{
    while (1)
    {
        if (Robot_Movement_Flag == Robot_ForWard_Flag)
        {
            Left_Distance = Ultrasonic_Get_Distance(Ultrasonic_Left);
            Center_Distance = Ultrasonic_Get_Distance(Ultrasonic_Center);
            Right_Distance = Ultrasonic_Get_Distance(Ultrasonic_Right);
            if (Center_Distance <= 10) 
            {
                if (Left_Distance < Right_Distance)
                {
                    Robot_Angle_Target = 90;
                    Robot_Movement_Flag = Robot_TurnRight_Flag;
                }
                else
                {
                    Robot_Angle_Target = -90;
                    Robot_Movement_Flag = Robot_TurnLeft_Flag;
                }
            }
            else if (Left_Distance <= 10 || Right_Distance <= 10 )
            {
                if (Left_Distance < Right_Distance)
                {
                    Robot_Angle_Target = 30;
                    Robot_Movement_Flag = Robot_TurnRight_Flag;
                }
                else
                {
                    Robot_Angle_Target = -30;
                    Robot_Movement_Flag = Robot_TurnLeft_Flag;
                }
            }
            else
            { 
                Robot_Movement_Flag = Robot_ForWard_Flag;
            }
        }
        RTOS_Delay_Task(100/Task_TickMiliSecond);
    }
    
}

static void MPU6050_Task(void)
{
    volatile uint16_t DelTa_Time = 0;
	volatile uint8_t Response = 0;
    unsigned char Angle_Rotation[6];
    while (1)
    {
        Disable_IRQ();
        DelTa_Time = MilliSecond_Stop();
        volatile int16_t Temp_Angle = 0;
        Response = MPU6050_Measure_Angle_Rotation(MPU6050_Z_Axis,DelTa_Time/1000.0,&Temp_Angle);
        MilliSecond_Start();
        if (Response == I2C_Success)
        {
            GPIO_WritePin(GPIOC,GPIO_Pin13,GPIO_Low);
            Robot_Angle_Target += Temp_Angle;
        }
        else
        {
            GPIO_WritePin(GPIOC,GPIO_Pin13,GPIO_High);
        }
        RTOS_Delay_Task(50/Task_TickMiliSecond);
        Enable_IRQ();
    }
    
}

static void Motor_Task(void)
{
    volatile uint8_t Robot_Left_Speed = 0;
    volatile uint8_t Robot_Right_Speed = 0;
    while (1)
    {
        if(Robot_Movement_Flag == Robot_ForWard_Flag)
        {
            if (Robot_PID_Result > 0)       
            {
                Robot_Right_Speed = 100;
                Robot_Left_Speed =(int8_t) 100 - Robot_PID_Result;
            }
            else
            {
                Robot_Left_Speed = 100;
                Robot_Right_Speed =(int8_t) 100 + Robot_PID_Result;
            }
            Robot_GoForward(Robot_Left_Speed,Robot_Right_Speed);
        }
        else if (Robot_Movement_Flag == Robot_TurnRight_Flag)
        {
            Robot_TurnRight((int8_t) -Robot_PID_Result);
            if (Robot_Angle_Target < 10 && Robot_Angle_Target > -10)
            {
                Robot_Movement_Flag = Robot_ForWard_Flag;
            }
        }
        else if (Robot_Movement_Flag == Robot_TurnLeft_Flag)
        {
            Robot_TurnLeft((int8_t) Robot_PID_Result);
        }
        RTOS_Delay_Task(50/Task_TickMiliSecond);
    }
    
}

int main()
{ 
    uint8_t Response =0;
    GPIO_SetMode(GPIOA,GPIO_Pin6,GPIO_Output_10MHz,GPIO_OP_GPPP);
    GPIO_WritePin(GPIOA,GPIO_Pin6,GPIO_High);
    GPIO_SetMode(GPIOA,GPIO_Pin7,GPIO_Output_10MHz,GPIO_OP_GPPP);
    GPIO_WritePin(GPIOA,GPIO_Pin7,GPIO_High);
    GPIO_SetMode(GPIOC,GPIO_Pin13,GPIO_Output_10MHz,GPIO_OP_GPPP);
    GPIO_WritePin(GPIOC,GPIO_Pin13,GPIO_High);
    Delay_Init(GetAHB_Clock());
    Delay_ms(1000);
    RTOS_Create_Task(&PID_Task,512,2,0x01);
    // RTOS_Create_Task(&Ultrasonic_Task,512,2,0x02);
    RTOS_Create_Task(&MPU6050_Task,512,2,0x03);
    
	RTOS_Create_Task(&Motor_Task,512,2,0x04);
    Robot_Setup();
    // Ultrasonic_Initialization();
    MilliSecond_Setup();
    Response = MPU6050_Setup();
    if (Response == I2C_Failure)
    {
        for(uint8_t i = 0;i<5;i++)
				{
					GPIO_WritePin(GPIOC,GPIO_Pin13,GPIO_High);
					Delay_ms(100);
					GPIO_WritePin(GPIOC,GPIO_Pin13,GPIO_Low);
					Delay_ms(100);
				}
        return 0;
    }
    MilliSecond_Start();
    // Ultrasonic_Trigger();
    RTOS_Run_Task();
    return 1;
}
