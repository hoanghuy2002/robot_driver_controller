#include "rtos.h"
#include "usart_driver.h"
#include "robot_driver.h"
#include "millisecond.h"
#include "systick_driver.h"
#include "ultrasonic.h"
#include "rcc_driver.h"
#include "mpu6050_driver.h"


int16_t Begin_Angle = 0;
int16_t Angle = 0;
float Filter_Value = 0;

int main()
{
    uint8_t Response = 0;
    SystickTimer_Init(GetAHB_Clock());
    MPU6050_Setup();
    MPU6050_Setfilter(MPU6050_Z_Axis,&Filter_Value);
    while (1)
    {
        int16_t Data = 0;
        SysTick_DelayMs(50);
        MPU6050_Measure_Angle_Rotation(MPU6050_Z_Axis,0.05,Filter_Value,&Data);
		Angle += Data-Begin_Angle;
    }
    
    
    
}