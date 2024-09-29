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

static void Count_Task(void)
{
    while ((1))
    {
        volatile static uint8_t data = 0;
        RTOS_Delay_Task(500/Task_TickMiliSecond);
        data +=1;
    }
    
}

int main()
{
    RTOS_Create_Task(&Count_Task,256,2,0xf2);
    RTOS_Run_Task();
    
    
    
}
