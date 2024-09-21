#include "mpu6050_driver.h"

#define MPU6050_Adrress 						0x68
#define Sample_Rate_Reg 						0x19
#define Configuration_Reg 					0x1A
#define Gyro_Config_Reg 						0x1B
#define Accelerometer_Config_Reg 		0x1C
#define INT_PIN_Reg 								0x37
#define INT_Enable_Reg 							0x38
#define Power_Management_1_Reg 			0x6B
#define Who_Am_I 										0x75

uint8_t MPU6050_Setup(I2C_RegStruct *I2C)
{
	uint8_t Response = 0;
	uint8_t DataSetup[2] = {Power_Management_1_Reg,0x01};
	Response = I2C_MasterTransmit(I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
		
	DataSetup[0] = Sample_Rate_Reg;
	DataSetup[1] = 99u;
	Response = I2C_MasterTransmit(I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
	
	DataSetup[0] = Configuration_Reg;
	DataSetup[1] = 1u;
	Response = I2C_MasterTransmit(I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
	
	DataSetup[0] = Gyro_Config_Reg;
	DataSetup[1] = 0x08;
	Response = I2C_MasterTransmit(I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
	
	DataSetup[0] = Accelerometer_Config_Reg;
	DataSetup[1] = 0x08;
	Response = I2C_MasterTransmit(I2C,I2C_7BitAddress,MPU6050_Adrress,(uint8_t *)DataSetup,2);
	if (Response == I2C_Failure) return I2C_Failure;
	
	return I2C_Success;
}

uint8_t MPU6050_ReadValue(I2C_RegStruct *I2C,uint8_t Register_Address, uint8_t *Buffer_Data)
{
	uint8_t Response = 0;
	Response = I2C_MasterTransmit(I2C,I2C_7BitAddress,MPU6050_Adrress,&Register_Address,1);
	if (Response == I2C_Failure) return I2C_Failure;
	Response = I2C_MasterReceive(I2C,I2C_7BitAddress,MPU6050_Adrress,Buffer_Data,1);
	return Response;
}




