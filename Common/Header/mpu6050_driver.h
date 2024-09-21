#include <stdint.h>
#include "i2c_driver.h"

#define MPU6050_Accel_X_Hight 		0x3B
#define MPU6050_Accel_X_Low				0x3C
#define MPU6050_Accel_Y_Hight 		0x3D
#define MPU6050_Accel_Y_Low				0x3E
#define MPU6050_Accel_Z_Hight 		0x3F
#define MPU6050_Accel_Z_Low				0x40

#define MPU6050_Temp_Hight				0x41
#define MPU6050_Temp_Low					0x42

#define MPU6050_Gyro_X_High				0x43
#define MPU6050_Gyro_X_Low				0x44
#define MPU6050_Gyro_Y_High				0x45
#define MPU6050_Gyro_Y_Low				0x46
#define MPU6050_Gyro_Z_High				0x47
#define MPU6050_Gyro_Z_Low				0x48


uint8_t MPU6050_Setup(I2C_RegStruct *I2C);
uint8_t MPU6050_ReadValue(I2C_RegStruct *I2C,uint8_t Register_Address, uint8_t *Buffer_Data);