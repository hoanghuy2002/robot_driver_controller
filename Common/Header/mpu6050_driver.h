#ifndef _MPU6050_DRIVER_H
#define _MPU6050_DRIVER_H

#include <stdint.h>
#include "i2c_driver.h"

#define MPU6050_x_Axis                          (uint8_t)0x3B
#define MPU6050_Y_Axis                          (uint8_t)0x3D
#define MPU6050_Z_Axis                          (uint8_t)0x3F


uint8_t MPU6050_Setup(void);
uint8_t MPU6050_Setfilter(uint8_t MPU6050_Axis,float *Filter_Value);
uint8_t MPU6050_ReadValue(uint8_t Register_Address, uint8_t *Buffer_Data);
uint8_t MPU6050_Measure_Angle_Rotation(uint8_t MPU6050_Axis,float Delta_Time,float Filter_Value, int16_t *Result);
uint8_t MPU6050_Measure_Acceleration(uint8_t MPU6050_Axis,float *Result);
#endif