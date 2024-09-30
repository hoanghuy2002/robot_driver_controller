#include "mpu6050_driver.h"
#include "rcc_driver.h"
#include <stdio.h>
#include <stdlib.h>


#define MPU6050_Adrress 						0x68
#define Sample_Rate_Reg 						0x19
#define Configuration_Reg 						0x1A
#define Gyro_Config_Reg 						0x1B
#define Accelerometer_Config_Reg 				0x1C
#define INT_PIN_Reg 							0x37
#define INT_Enable_Reg 							0x38
#define Power_Management_1_Reg 					0x6B
#define Who_Am_I 								0x75

#define MPU6050_I2C								I2C1

static float Filter_Value = 0;
static void MPU6050_I2C_Setup()
{
	I2C_ConfigStruct I2C_Custom;
	I2C_Custom.I2C = MPU6050_I2C;
	I2C_Custom.I2C_ACK = I2C_ACK_Enable;
	I2C_Custom.I2C_ClockStretch = I2C_ClockStretch_Enable;
	I2C_Custom.I2C_GeneralCall = I2C_GeneralCall_Disable;
	I2C_Custom.I2C_NumberBitAddress = I2C_7BitAddress;
	I2C_Custom.I2C_OwnAddress = 0x20;
	I2C_Custom.I2C_SpeedMode = I2C_Standar_SpeedMode;
	I2C_Custom.I2C_APBClockInput = GetAPB1_Clock();
	I2C_Custom.I2C_SCLFrequency = (uint32_t)100000;
	I2C_Init(&I2C_Custom);
}

uint8_t MPU6050_Setfilter(uint8_t MPU6050_Axis,float *Filter_Value)
{
	uint8_t *Raw_Data = (uint8_t *)malloc(2*sizeof(uint8_t));
	uint8_t Response = 0;
	for (uint8_t Loop_Count = 100;Loop_Count>0;Loop_Count--)
	{
		Response = MPU6050_ReadValue((uint8_t)MPU6050_Axis+8,Raw_Data+1);			// Read Gyro_Axis High value 
		if (Response == I2C_Failure) return I2C_Failure;
		Response = MPU6050_ReadValue((uint8_t)MPU6050_Axis+9,Raw_Data);		// Read Gyro_Axis Low Value
		if (Response == I2C_Failure) return I2C_Failure;
		*Filter_Value += (float)(((int16_t)(*(Raw_Data+1)<<8|*Raw_Data))/65.5);
	}
	*Filter_Value = *Filter_Value/100.0;
	free(Raw_Data);
	return I2C_Success;

}

uint8_t MPU6050_Setup()
{
	uint8_t Response = 0;
	uint8_t DataSetup[2] = {Power_Management_1_Reg,0x01};
	MPU6050_I2C_Setup();
	Response = I2C_MasterTransmit(MPU6050_I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
		
	DataSetup[0] = Sample_Rate_Reg;
	DataSetup[1] = 99u;
	Response = I2C_MasterTransmit(MPU6050_I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
	
	DataSetup[0] = Configuration_Reg;
	DataSetup[1] = 1u;
	Response = I2C_MasterTransmit(MPU6050_I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
	
	DataSetup[0] = Gyro_Config_Reg;
	DataSetup[1] = 0x08;
	Response = I2C_MasterTransmit(MPU6050_I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
	
	DataSetup[0] = Accelerometer_Config_Reg;
	DataSetup[1] = 0x08;
	Response = I2C_MasterTransmit(MPU6050_I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;

	MPU6050_Setfilter(MPU6050_Z_Axis,&Filter_Value);
	return I2C_Success;
}

uint8_t MPU6050_ReadValue(uint8_t Register_Address, uint8_t *Buffer_Data)
{
	uint8_t Response = 0;
	Response = I2C_MasterTransmit(MPU6050_I2C,I2C_7BitAddress,MPU6050_Adrress,&Register_Address,1);
	if (Response == I2C_Failure) return I2C_Failure;
	Response = I2C_MasterReceive(MPU6050_I2C,I2C_7BitAddress,MPU6050_Adrress,Buffer_Data,1);
	return Response;
}

uint8_t MPU6050_Measure_Angle_Rotation(uint8_t MPU6050_Axis,float Delta_Time, int16_t *Result)
{
	uint8_t Response = 0;
	uint8_t *Raw_Data = (uint8_t *) malloc(2*sizeof(uint8_t));
	int16_t Temp = 0;
	Response = MPU6050_ReadValue(MPU6050_Axis+8,Raw_Data);			// Read Gyro_Axis High value 
	if (Response == I2C_Failure) return I2C_Failure;
	Response = MPU6050_ReadValue(MPU6050_Axis+9,Raw_Data+1);		// Read Gyro_Axis Low Value
	if (Response == I2C_Failure) return I2C_Failure;
	Temp = (int16_t)(*Raw_Data<<8|*(Raw_Data+1));
	Temp = (int16_t)(((Temp/65.5)-Filter_Value)*Delta_Time);
	*Result = Temp;
	free(Raw_Data);
	return I2C_Success;
}

uint8_t MPU6050_Measure_Acceleration(uint8_t MPU6050_Axis,float *Result)
{
	uint8_t Response = 0;
	uint8_t *Raw_Data = (uint8_t *) malloc(2*sizeof(uint8_t));
	Response = MPU6050_ReadValue((uint8_t)MPU6050_Axis,Raw_Data);			// Read Acc_Axis High value 
	if (Response == I2C_Failure) return I2C_Failure;
	Response = MPU6050_ReadValue((uint8_t)MPU6050_Axis+1,Raw_Data+1);		// Read Acc_Axis Low Value
	if (Response == I2C_Failure) return I2C_Failure;
	*Result = ((*Raw_Data<<8|*(Raw_Data+1))/8192.0);
	return I2C_Success;
}





