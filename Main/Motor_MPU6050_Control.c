#include <stdio.h>
#include "rtos.h"
#include "robot_driver.h"
#include "ultrasonic.h"
#include "cortexm3_irq.h"
#include "serial_driver.h"
#include "rcc_driver.h"
#include "String_Handler.h"
#include <string.h>
#include <stdlib.h>


#define Rotation_Kp                  0.5
#define Rotation_Ki                  0.04
#define Rotation_Kd                  0.1

#define Movement_Kp                  1.3
#define Movement_Ki                  0.1
#define Movement_Kd                  0.1

#define PID_Delta_Time               0.05

#define Robot_Stop_Flag             0
#define Robot_Movement_Flag         1
#define Robot_Rotation_Flag         2






static int8_t Robot_State_Flag = Robot_Stop_Flag;
volatile float Robot_Angle = 0;     // Turn-Right => Robot_Angle > 0 || Turn-Left -> Robot_Angle < 0 
volatile float Robot_Distance = 0;


volatile float Error_Before = 0;
volatile float Error_Total = 0;
volatile float Error = 0;
volatile float Robot_PID_Result = 0;

static void Reset_PID_Parameter(void)
{
    Error_Total = 0;
    Error_Before = 0;
    Error = 0;
    Robot_PID_Result = 0;
}

static void PID_Controller_Task(void)
{
    while ((1))
    {
        if (Robot_State_Flag == Robot_Rotation_Flag)
        {
            Error =(float)(0 - Robot_Angle);
            Robot_PID_Result = Error*Rotation_Kp + (Error-Error_Before)*Rotation_Kd/PID_Delta_Time + Error_Total*Rotation_Ki*PID_Delta_Time;
            Robot_PID_Result = (Robot_PID_Result/90)*100;
            Error_Before = Error;
            Error_Total += Error;
            if (Robot_PID_Result>100) Robot_PID_Result = 100;
            else if (Robot_PID_Result<-100) Robot_PID_Result = -100;
        }
        else if (Robot_State_Flag == Robot_Movement_Flag)
        {
            Error =(float)(0 - Robot_Distance);
            Robot_PID_Result = Error*Movement_Kp + (Error-Error_Before)*Movement_Kd/PID_Delta_Time + Error_Total*Movement_Ki*PID_Delta_Time;
            Robot_PID_Result = (Robot_PID_Result/40)*100;           // 40 cm
            Error_Before = Error;
            Error_Total += Error;
            if (Robot_PID_Result>100) Robot_PID_Result = 100;
            else if (Robot_PID_Result<-100) Robot_PID_Result = -100;
        }
        else
        {
            // Dont do anything
        }
        
        RTOS_Delay_Task(50/Task_TickMiliSecond);
    }
    
}

// static void Ultrasonic_Task(void)
// {
//     while (1)
//     {
//         if (Robot_Movement_Flag == Robot_ForWard_Flag)
//         {
//             Left_Distance = Ultrasonic_Get_Distance(Ultrasonic_Left);
//             Center_Distance = Ultrasonic_Get_Distance(Ultrasonic_Center);
//             Right_Distance = Ultrasonic_Get_Distance(Ultrasonic_Right);
//             if (Center_Distance <= 10) 
//             {
//                 if (Left_Distance < Right_Distance)
//                 {
//                     Robot_Angle_Target = 90;
//                     Robot_Movement_Flag = Robot_TurnRight_Flag;
//                 }
//                 else
//                 {
//                     Robot_Angle_Target = -90;
//                     Robot_Movement_Flag = Robot_TurnLeft_Flag;
//                 }
//             }
//             else if (Left_Distance <= 10 || Right_Distance <= 10 )
//             {
//                 if (Left_Distance < Right_Distance)
//                 {
//                     Robot_Angle_Target = 30;
//                     Robot_Movement_Flag = Robot_TurnRight_Flag;
//                 }
//                 else
//                 {
//                     Robot_Angle_Target = -30;
//                     Robot_Movement_Flag = Robot_TurnLeft_Flag;
//                 }
//             }
//             else
//             { 
//                 Robot_Movement_Flag = Robot_ForWard_Flag;
//             }
//         }
//         RTOS_Delay_Task(50/Task_TickMiliSecond);
//     }
    
// }


static void Distance_Angle_Calculation(void)
{
    while (1)
    {
        if (Robot_State_Flag == Robot_Rotation_Flag)
        {
            Robot_Angle += Robot_Get_Instantaneous_Angle();
        }
        else if (Robot_State_Flag == Robot_Movement_Flag)
        {
            Robot_Distance -= Robot_Get_Instantaneous_Distance();
        }
        else
        {
            // Dont do anything
        }
        RTOS_Delay_Task(50/Task_TickMiliSecond);
    }
    
}

static void Motor_Task(void)
{
    uint8_t Finish_Count = 0;
    while (1)
    {
        if (Robot_State_Flag == Robot_Rotation_Flag)
        {
            if (Robot_PID_Result < 0)
            {
                int8_t Speed_Percent =(int8_t) -Robot_PID_Result;
                Robot_TurnRight(Speed_Percent);
            }
            else 
            {
                int8_t Speed_Percent =(int8_t) Robot_PID_Result;
                Robot_TurnLeft(Speed_Percent);
            }
            
        }
        else if (Robot_State_Flag ==Robot_Movement_Flag)
        {
            if (Robot_PID_Result < 0)           // need foward
            {
                int8_t Speed_Percent = (int8_t) - Robot_PID_Result;
                Robot_GoForward(Speed_Percent,Speed_Percent);
            }
            else
            {
                int8_t Speed_Percent = (int8_t) Robot_PID_Result;
                Robot_GoBackward(Speed_Percent,Speed_Percent);
            }
            
        }
        else
        {
            Robot_Stop();
        }

        if (Error < 3 && Error > -3)
        {
            Finish_Count ++;
        }
        else
        {
            Finish_Count = 0;
        }
        if (Finish_Count == 3)
        {
            if (Robot_State_Flag == Robot_Rotation_Flag)
            {
                Serial_Write("Rotation_Okay\n");
            }
            else if (Robot_State_Flag == Robot_Movement_Flag)
            {
                Serial_Write("Movement_Okay\n");
            }
            
            Robot_State_Flag = Robot_Stop_Flag;
        }
        
        RTOS_Delay_Task(50/Task_TickMiliSecond);
        
    }
    
}

static void Serial_Data_Callback(void)
{
    char *Buffer_Pointer =(char *) Serial_Read();
    if (String_Compare(Buffer_Pointer,"Foward"))
    {
        Robot_State_Flag = Robot_Movement_Flag;
        Robot_Distance = 40;
    }
    else if (String_Compare(Buffer_Pointer,"Backward"))
    {
        Robot_State_Flag = Robot_Movement_Flag;
        Robot_Distance = -40;
    }
    else if (String_Check_Data_In_String(Buffer_Pointer,"Rotate-Right"))
    {
        int8_t First_Index_Of_Numer = String_Find_Index_Of_Character(Buffer_Pointer,"/") + 1;
        Robot_Angle = (float) String_Convert_String_To_IntergerNumber((Buffer_Pointer + First_Index_Of_Numer));
        Robot_State_Flag = Robot_Rotation_Flag;
    }
    else if (String_Check_Data_In_String(Buffer_Pointer,"Rotate-Left"))
    {
        int8_t First_Index_Of_Numer = String_Find_Index_Of_Character(Buffer_Pointer,"/") + 1;
        Robot_Angle = (float) (String_Convert_String_To_IntergerNumber((Buffer_Pointer + First_Index_Of_Numer))*-1.0);
        Robot_State_Flag = Robot_Rotation_Flag;
    }
    else
    {

    }
    
    
    
}



int main()
{ 
    RTOS_Create_Task(&PID_Controller_Task,512,2,0x01);
    // // RTOS_Create_Task(&Ultrasonic_Task,512,2,0x02);
    RTOS_Create_Task(&Distance_Angle_Calculation,512,2,0x03);
	RTOS_Create_Task(&Motor_Task,512,2,0x05);
    Robot_Setup();
    Robot_Start_Measure_Distance();
    Serial_Initialization(&Serial_Data_Callback);
    // Ultrasonic_Initialization();
    // Ultrasonic_Trigger();
    RTOS_Run_Task();
    return 1;
}
