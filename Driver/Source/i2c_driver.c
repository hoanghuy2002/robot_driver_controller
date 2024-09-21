#include "i2c_driver.h"
#include "gpio_driver.h"


void I2C_Init(I2C_ConfigStruct *I2C_Config)
{
	/*Enable Peripheral,Clock and GPIO I2C Configuration*/
	if(I2C_Config->I2C == I2C1)
	{
		I2C1_EnableCLK();
		/*Check I2C Remapping*/
		if((AFIO->MAPR &0x02))   /*I2C1 Remapping*/
		{
			GPIO_SetMode(GPIOB,GPIO_Pin8,GPIO_Output_10MHz,GPIO_OP_AFOD);		/*SCL Pin: PB8*/
			GPIO_SetMode(GPIOB,GPIO_Pin9,GPIO_Output_10MHz,GPIO_OP_AFOD);		/*SDA Pin: PB9*/
		}
		else 										/*I2C1  Doesn't remap*/
		{
			GPIO_SetMode(GPIOB,GPIO_Pin6,GPIO_Output_10MHz,GPIO_OP_AFOD);		/*SCL Pin: PB6*/
			GPIO_SetMode(GPIOB,GPIO_Pin7,GPIO_Output_10MHz,GPIO_OP_AFOD);		/*SDA Pin: PB7*/
		}
		I2C1_Enable();
	}
	else if (I2C_Config->I2C == I2C2)
	{
		I2C2_EnableCLK();
		GPIO_SetMode(GPIOB,GPIO_Pin10,GPIO_Output_10MHz,GPIO_OP_AFOD);		/*SCL Pin: PB10*/
		GPIO_SetMode(GPIOB,GPIO_Pin11,GPIO_Output_10MHz,GPIO_OP_AFOD);		/*SDA Pin: PB11*/
		I2C2_Enable();
	}
	/*Reset ACK NOSTRETCH ENGC Bit*/
	I2C_Config->I2C->CR1 &= 0xFB3F;
	/*ACK, Clock Stretching and General Call Configuration*/
	I2C_Config->I2C->CR1 |=  (uint32_t)((I2C_Config->I2C_ACK<<10)|(I2C_Config->I2C_ClockStretch<<7)|(I2C_Config->I2C_GeneralCall<<6));
	/*Own Number Bit Address Configuration*/
	I2C_Config->I2C->OAR1 &= ~(uint32_t)(1<<15);
	I2C_Config->I2C->OAR1 |=  (uint32_t)(I2C_Config->I2C_NumberBitAddress<<15);
	/*Own Address Configuration*/
	if(I2C_Config->I2C_NumberBitAddress == I2C_7BitAddress)
	{
		I2C_Config->I2C->OAR1 = (uint32_t)I2C_Config->I2C_OwnAddress<<1;
	}
	else if(I2C_Config->I2C_NumberBitAddress == I2C_10BitAddress)
	{
		I2C_Config->I2C->OAR1 = (uint32_t)I2C_Config->I2C_OwnAddress;
	}
	/*Clock Input Configuration*/
	I2C_Config->I2C->CR2 &= 0xFFFFFF00;
	I2C_Config->I2C->CR2 |= I2C_Config->I2C_APBClockInput/1000000;
	/*Speed Mode,SCL Clock Frequency and Time Rise Configuration*/
	I2C_Config->I2C->CCR &= 0xFFFF0000;
	I2C_Config->I2C->TRISE &= 0x00;
	if(I2C_Config->I2C_SpeedMode == I2C_Standar_SpeedMode)
	{
		I2C_Config->I2C->CCR |= I2C_Config->I2C_APBClockInput/(2*I2C_Config->I2C_SCLFrequency);
		I2C_Config->I2C->TRISE = (I2C_Config->I2C_APBClockInput/1000000)+1;
	}
	else if(I2C_Config->I2C_SpeedMode == I2C_Fast_2_SpeedMode)
	{
		I2C_Config->I2C->CCR |= I2C_Config->I2C_APBClockInput/(3*I2C_Config->I2C_SCLFrequency)|(1<<15);
		I2C_Config->I2C->TRISE = (I2C_Config->I2C_APBClockInput/4000000)+1;
	}
	else if(I2C_Config->I2C_SpeedMode == I2C_Fast_16_9_SpeedMode)
	{
		I2C_Config->I2C->CCR |= I2C_Config->I2C_APBClockInput/(25*I2C_Config->I2C_SCLFrequency)|(3<<14);
		I2C_Config->I2C->TRISE = (I2C_Config->I2C_APBClockInput/4000000)+1;
	}
	
}

uint8_t I2C_SendStartSignal(I2C_RegStruct *I2C)
{
	uint32_t TimeOut = 0;
	/*Send Start Signal*/
	I2C->CR1 |= (1<<8);
	/*Wait to SB Bit is Set*/
	while((I2C->SR1 &0x01)==0)
	{
		TimeOut ++;
		if(TimeOut == 10000000) return I2C_Failure;
	}
	return I2C_Success;
}

uint8_t I2C_SendStopSignal(I2C_RegStruct *I2C)
{
	uint32_t Timeout = 0;
	I2C->CR1 |= (1<<9);			/*Send Stop Signal*/
	return I2C_Success;
}

uint8_t I2C_SendAddress(I2C_RegStruct *I2C,uint8_t I2C_NumberBitAddress,uint16_t I2C_SlaveAddress,uint8_t I2C_Direction)
{
	uint8_t Count =0;
	uint32_t Timeout = 0;
	if(I2C_NumberBitAddress == I2C_7BitAddress)
	{
		/*Send Address*/
		SendAddress:
		I2C->DR = (uint32_t)((I2C_SlaveAddress<<1)|I2C_Direction);
		/*Wait ADDR Bit is set*/
		while((I2C->SR1&0x02)==0)
		{
			Timeout++;
			if(Timeout == 10000000) return I2C_Failure;
			/*Acknowledge Failure*/
			if(I2C->SR1 &(1<<10))
			{
				Count++;
				if(Count ==3) return I2C_Failure;
				goto SendAddress;
			}
		}
		/*Clear ADDR Bit*/
		I2C->SR2;
	}
	
	else if(I2C_NumberBitAddress == I2C_10BitAddress)
	{
		Count =0;
		SendHeader:
		I2C->DR = (0xF0)|((I2C_SlaveAddress&0x300)>>7)|I2C_Direction;
		/*Wait ADD10 Bit is set*/
		while((I2C->SR1&0x08)==0)
		{
			/*Acknowledge Failure*/
			if(I2C->SR1 &(1<<10))
			{
				Count++;
				if(Count ==3) return I2C_Failure;
				goto SendHeader;
			}
		}
		Count =0;
		SendAddress2:
		I2C->DR = I2C_SlaveAddress&0xFF;
		/*Wait ADDR Bit is set*/
		while((I2C->SR1&0x02)==0)
		{
			/*Acknowledge Failure*/
			if(I2C->SR1 &(1<<10))
			{
				Count++;
				if(Count ==3) return I2C_Failure;
				goto SendAddress2;
			}
		}
		/*Clear ADDR Bit*/
		I2C->SR2;
		if(I2C_Direction == I2C_Receiver)
		{
			I2C_SendStartSignal(I2C);									/*Repeat Start*/
		}
	}
	return I2C_Success;
	
}

uint8_t I2C_MasterTransmit(I2C_RegStruct *I2C,uint8_t I2C_NumberBitAddress,uint16_t I2C_SlaveAddress,uint8_t *TransmitBuffer,uint8_t BufferLength)
{
	uint32_t Timeout = 0;
	uint8_t Response = I2C_SendStartSignal(I2C);
	if (Response == I2C_Failure) return I2C_Failure;
	Response = I2C_SendAddress(I2C,I2C_NumberBitAddress,I2C_SlaveAddress,I2C_Transmitter);
	if (Response == I2C_Failure) return I2C_Failure;
	
	for(uint8_t Buffer_Index=0;Buffer_Index<BufferLength;Buffer_Index++)
	{
		/*Wait TXE Bit is Set*/
		while((I2C->SR1&0x80)==0)
		{
			Timeout++;
			if(Timeout==10000000) return I2C_Failure;				
		}
		I2C->DR = *TransmitBuffer;
		TransmitBuffer++;
		Timeout =0;
	}
	/*Wait TXE Bit is Set*/
	while((I2C->SR1&0x80)==0)
	{
		Timeout++;
		if(Timeout==10000000) return I2C_Failure;				
	}
	Timeout = 0;
	/*Wait BTF Bit is Set*/
	while((I2C->SR1&0x04)==0)
	{
		Timeout++;
		if(Timeout==10000000) return I2C_Failure;				
	}
	/*Send Stop Signal*/
	Response = I2C_SendStopSignal(I2C);
	if(Response == I2C_Failure) return I2C_Failure;
	else return I2C_Success;
}

uint8_t I2C_MasterReceive(I2C_RegStruct *I2C,uint8_t I2C_NumberBitAddress,uint16_t I2C_SlaveAddress,uint8_t *ReceiveBuffer,uint8_t BufferLength)
{
	uint32_t Timeout = 0;
	uint8_t Response = I2C_SendStartSignal(I2C);
	if (Response == I2C_Failure) return I2C_Failure;
	Response = I2C_SendAddress(I2C,I2C_NumberBitAddress,I2C_SlaveAddress,I2C_Receiver);
	if (Response == I2C_Failure) return I2C_Failure;
	if(BufferLength == 1)
	{
			I2C->CR1 &= ~(uint32_t)(1<<10);  						/*Reset ACK Bit*/
			Response = I2C_SendStopSignal(I2C);										/*Set Stop Bit*/
			if (Response == I2C_Failure) return I2C_Failure;
			while((I2C->SR1&(1<<6))==0)								  /*Wait to RXNE Bit is Set*/
			{
				Timeout++;
				if(Timeout == 10000000) return I2C_Failure;
			}
			*ReceiveBuffer = (uint8_t) I2C->DR;					/*Read Data*/
	}
	else
	{
		for(uint8_t Buffer_Index =BufferLength;Buffer_Index>0;Buffer_Index--)
		{
			while((I2C->SR1&(1<<6))==0)									/*Wait to RXNE Bit is Set*/
			{
				Timeout++;
				if(Timeout == 10000000) return I2C_Failure;
			}
			if(Buffer_Index == 2)																	/*If last 2 bit remaining*/
			{
				I2C->CR1 &= ~(uint32_t)(1<<10);  					/*Reset ACK Bit*/
				Response = I2C_SendStopSignal(I2C);									/*Set Stop Bit*/
				if (Response == I2C_Failure) return I2C_Failure;
			}
			*ReceiveBuffer = (uint8_t) I2C->DR;					/*Read Data*/
			ReceiveBuffer++;
			Timeout = 0;
		}
	}
	return I2C_Success;

}



void I2C_IRQRegister(I2C_IRQStruct *I2C_IRQ)
{
	uint8_t IRQ_Number =0;
	Disable_IRQ();
	/*Reset ITBUFEN, ITEVTEN, ITERREN Bit*/
	I2C_IRQ->I2C->CR2 &= 0xF8FF;
	I2C_IRQ->I2C->CR2 |= (uint32_t)((I2C_IRQ->I2C_BufferIRQ<<9)|(I2C_IRQ->I2C_EventIRQ)|(I2C_IRQ->I2C_ErrorIRQ));
	/*Finding IRQ Number*/
	if(I2C_IRQ->I2C == I2C1)
	{
		IRQ_Number =31;
	}
	else if(I2C_IRQ->I2C == I2C2)
	{
		IRQ_Number =33;
	}
	/*Configure NVIC*/
	if(I2C_IRQ->I2C_EventIRQ)
	{
		NVIC_Enable_IRQ(IRQ_Number);
		NVIC_SetPriority_IRQ(IRQ_Number,I2C_IRQ->I2C_EventIRQPriority);
	}
	if(I2C_IRQ->I2C_ErrorIRQ)
	{
		NVIC_Enable_IRQ(IRQ_Number+1);
		NVIC_SetPriority_IRQ(IRQ_Number+1,I2C_IRQ->I2C_ErrorIRQPriority);
	}
	Enable_IRQ();
}





