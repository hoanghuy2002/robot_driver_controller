#ifndef _I2C_DRIVER_H_
#define _I2C_DRIVER_H_
#include "stm32f103.h"



/*Clock Control*/
#define I2C1_EnableCLK()						(RCC->APB1ENR|=(1<<21))
#define I2C2_EnableCLK()						(RCC->APB1ENR|=(1<<22))

#define I2C1_DisableCLK()						(RCC->APB1ENR&=~(uint32_t)(1<<21))
#define I2C2_DisableCLK()						(RCC->APB1ENR&=~(uint32_t)(1<<22))

#define I2C1_Enable()									(I2C1->CR1 |= (1<<0))
#define I2C2_Enable()									(I2C2->CR1 |= (1<<0))

#define I2C1_Disable()								(I2C1->CR1 &= ~(uint32_t)(1<<0))
#define I2C2_Disable()								(I2C2->CR1 &= ~(uint32_t)(1<<0))

typedef struct
{
	I2C_RegStruct *I2C;
	uint32_t 			I2C_SCLFrequency;
	uint32_t 			I2C_APBClockInput;
	uint8_t 			I2C_ACK;
	uint8_t 			I2C_ClockStretch;
	uint8_t 			I2C_GeneralCall;
	uint8_t 			I2C_NumberBitAddress;
	uint16_t 			I2C_OwnAddress;
	uint8_t 			I2C_SpeedMode;
}I2C_ConfigStruct;

typedef struct
{
	I2C_RegStruct *I2C;
	uint8_t I2C_BufferIRQ;
	uint8_t I2C_EventIRQ;
	uint8_t I2C_ErrorIRQ;
	uint8_t I2C_EventIRQPriority;
	uint8_t I2C_ErrorIRQPriority;
}I2C_IRQStruct;


void I2C_Init(I2C_ConfigStruct *I2C_Config);
uint8_t I2C_SendStartSignal(I2C_RegStruct *I2C);
uint8_t I2C_SendStopSignal(I2C_RegStruct *I2C);
uint8_t I2C_SendAddress(I2C_RegStruct *I2C,uint8_t I2C_NumberBitAddress,uint16_t I2C_Address,uint8_t I2C_Direction);
uint8_t I2C_MasterTransmit(I2C_RegStruct *I2C,uint8_t I2C_NumberBitAddress,uint16_t I2C_SlaveAddress,uint8_t *TransmitBuffer,uint8_t BufferLength);
uint8_t I2C_MasterReceive(I2C_RegStruct *I2C,uint8_t I2C_NumberBitAddress,uint16_t I2C_SlaveAddress,uint8_t *ReceiveBuffer,uint8_t BufferLength);
void I2C_IRQRegister(I2C_IRQStruct *I2C_IRQ);
void I2C1_EV_IRQHandler(void);
void I2C1_ER_IRQHandler(void);
void I2C2_EV_IRQHandler(void);
void I2C2_ER_IRQHandler(void);


/*Possible Parameters for Functions and Structs of I2C*/
/**/
/**/
/*I2C_ACK*/
#define I2C_ACK_Enable								1U
#define I2C_ACK_Disable								0U
/*I2C_ClockStretch*/
#define I2C_ClockStretch_Enable				0U
#define I2C_ClockStretch_Disable			1U
/*I2C_GeneralCall*/
#define I2C_GeneralCall_Enable				1U
#define I2C_GeneralCall_Disable				0U
/*I2C_NumberBitAddress*/
#define I2C_10BitAddress							1U
#define I2C_7BitAddress								0U
/*I2C_SpeedMode*/
#define I2C_Standar_SpeedMode					0U
#define I2C_Fast_2_SpeedMode					2U
#define I2C_Fast_16_9_SpeedMode				3U

/*I2C_Direction*/
#define I2C_Transmitter								0U
#define I2C_Receiver									1U

/*I2C_BufferIRQ*/
#define I2C_BufferIRQ_Enable					3U
#define I2C_BufferIRQ_Disable					0U
/*I2C_EventIRQ*/
#define I2C_EventIRQ_Enable						1U
#define I2C_EventIRQ_Disable					0U
/*I2C_ErrorIRQ*/
#define I2C_ErrorIRQ_Enable						1U
#define I2C_ErrorIRQ_Disable					0U

/*I2C_Status*/
#define I2C_Success										1U
#define I2C_Failure										0U

#endif

