#include "usart_driver.h"
#include "rcc_driver.h"
#include "cortexm3_irq.h"
#include "gpio_driver.h"
#include <stdlib.h>

typedef void(*Function_CallBack)(uint8_t);
Function_CallBack Handler_CallBack;




void USART_Init(USART_ConfigStruct *USART_Config)
{
	uint32_t USART_CLK =0;
	
	/*Enable Pin use for USART*/
	/*Enable Clock Peripheral for USART*/
	if(USART_Config->USART == USART1)
	{
		USART1_EnableCLK();
		USART_CLK = GetAPB2_Clock();
		switch(USART_Config->USART_Mode)
		{
			case USART_RX_Mode: 	GPIO_SetMode(GPIOA,GPIO_Pin10,GPIO_Input,GPIO_IP_PUPD);
									break;
			case USART_TX_Mode: 	GPIO_SetMode(GPIOA,GPIO_Pin9,GPIO_Output_10MHz,GPIO_OP_AFPP);
									break;
			case USART_TXRX_Mode:	GPIO_SetMode(GPIOA,GPIO_Pin10,GPIO_Input,GPIO_IP_PUPD);
									GPIO_SetMode(GPIOA,GPIO_Pin9,GPIO_Output_10MHz,GPIO_OP_AFPP);
									break;
		}
	}
	else if(USART_Config->USART == USART2)
	{
		USART2_EnableCLK();
		USART_CLK = GetAPB1_Clock();
		switch(USART_Config->USART_Mode)
		{
			case USART_RX_Mode: 	GPIO_SetMode(GPIOA,GPIO_Pin3,GPIO_Input,GPIO_IP_PUPD);
									break;
			case USART_TX_Mode: 	GPIO_SetMode(GPIOA,GPIO_Pin2,GPIO_Output_10MHz,GPIO_OP_AFPP);
									break;
			case USART_TXRX_Mode:	GPIO_SetMode(GPIOA,GPIO_Pin3,GPIO_Input,GPIO_IP_PUPD);
									GPIO_SetMode(GPIOA,GPIO_Pin2,GPIO_Output_10MHz,GPIO_OP_AFPP);
									break;
		}
	}
	else if(USART_Config->USART == USART3)
	{
		USART3_EnableCLK();
		USART_CLK = GetAPB1_Clock();
		switch(USART_Config->USART_Mode)
		{
			case USART_RX_Mode: 	GPIO_SetMode(GPIOB,GPIO_Pin11,GPIO_Input,GPIO_IP_PUPD);
									break;
			case USART_TX_Mode: 	GPIO_SetMode(GPIOB,GPIO_Pin10,GPIO_Output_10MHz,GPIO_OP_AFPP);
									break;
			case USART_TXRX_Mode:	GPIO_SetMode(GPIOB,GPIO_Pin11,GPIO_Input,GPIO_IP_PUPD);
									GPIO_SetMode(GPIOB,GPIO_Pin11,GPIO_Output_10MHz,GPIO_OP_AFPP);
									break;
		}
	}
	/*Configuration of USART Mode*/
	USART_Config->USART->CR1 &= ~(uint32_t)(3<<2);
	USART_Config->USART->CR1 |= (uint32_t)(USART_Config->USART_Mode<<2);
	/*Configuration of USART Word Length*/
	USART_Config->USART->CR1 &= ~(uint32_t)(USART_Config->USART_WordLength<<12);
	USART_Config->USART->CR1 |= (uint32_t)(USART_Config->USART_WordLength<<12);
	/*Configuration of USART Number Stop bit*/
	USART_Config->USART->CR2 &= ~(uint32_t)(USART_Config->USART_StopBit<<12);
	USART_Config->USART->CR2 |= (uint32_t)(USART_Config->USART_StopBit<<12);
	/*Configuration of USART Parity Opntion*/
	USART_Config->USART->CR1 &= ~(uint32_t)(USART_Config->USART_Parity<<9);
	USART_Config->USART->CR1 |= (uint32_t)(USART_Config->USART_Parity<<9);
	/*Configuration of USART Hardwear Flow Control*/
	USART_Config->USART->CR3 &= ~(uint32_t)(USART_Config->USART_HWFlowControl<<8);
	USART_Config->USART->CR3 |= (uint32_t)(USART_Config->USART_HWFlowControl<<8);
	/*Configuration of USART Baudrate*/
	double USARTDIV = (double)(USART_CLK)/(USART_Config->USART_Baudrate*16);
	uint16_t DIV_Mantissa =(uint16_t) USARTDIV;
	float Frac =  (float) ((USARTDIV - DIV_Mantissa)*16);
	uint8_t DIV_Fraction = (uint8_t) Frac;
	if((float)Frac-DIV_Fraction >= (float)0.5)
	{
		DIV_Fraction +=1;
	}
	if (DIV_Fraction ==16)
	{
		DIV_Fraction =0;
		DIV_Mantissa +=1;
	}
	uint32_t data = (uint32_t)(DIV_Fraction)|(uint32_t)(DIV_Mantissa<<4);
	USART_Config->USART->BRR = data;
	USART_Config->USART->CR1 |= (1<<13);
}

void USART_WriteData(USART_RegStruct *USART, uint8_t *Buffer,uint8_t Buffer_Length)
{
	for (uint8_t i =0;i<Buffer_Length;i++)
	{
		/*Wait for TXE Flag is set*/
		while((USART->SR&(uint32_t)(1<<7))==0);
		/*Check USART Word Length 8 or 9 Bit*/
		if((USART->CR1&(uint32_t)(1<<12)) !=0)
		{
			/*USART Word Length is 9 Bit*/
			
			/* Check USART Parity Bit option*/
			if((USART->CR1&(uint32_t)(1<<10))!= 0)
			{
				/*USART Config Parity Bit Enable*/
				USART->DR = (uint32_t)*Buffer;
				Buffer++;
			}
			else
			{
				/*USART Config Parity Bit Disable*/
				uint16_t *pData;
				pData = (uint16_t*)Buffer;
				USART->DR = (uint32_t)(*pData&(uint16_t)0x01FF);
				Buffer+=2;
			}
		}
		else
		{
			USART->DR |= (uint32_t)*(Buffer+i);
		}
			
	}
}

void USART_ReadData(USART_RegStruct *USART, uint8_t *Buffer)
{
		/*Wait for RXNE Flag is set*/
		while((USART->SR&(uint32_t)(1<<5))==0);
		/*Check USART Word Length 8 or 9 Bit*/
		if((USART->CR1&(uint32_t)(1<<12)) !=0)
		{
			/*USART Word Length is 9 Bit*/
			
			/* Check USART Parity Bit option*/
			if((USART->CR1&(uint32_t)(1<<10))!= 0)
			{
				/*USART Config Parity Bit Enable*/
				*Buffer = (uint8_t)USART->DR;
			}
			else
			{
				/*USART Config Parity Bit Disable*/
				*(uint16_t *)Buffer = (uint16_t)(USART->DR&0x01FF);
			}
		}
		else
		{
			*Buffer = (uint8_t)(USART->DR&0x7F);
		}
	
}



void USART_RegisterEvent(USART_RegStruct *USART,uint8_t USART_Event,uint8_t IRQ_Priority,void (*Event_Handler)(uint8_t))
{
	Disable_IRQ();
	Handler_CallBack = Event_Handler;
	if(USART_Event ==0)
	{
		USART->CR3 |= (1<<0);
	}
	else if(USART_Event == 0xFF)
	{
		USART->CR1 |= (uint32_t)(0x01F0);
		USART->CR3 |= (1<<0);
	}
	else
	{
		USART->CR1 |= (uint32_t)(1<<USART_Event);
	}
	if(USART == USART1)
	{
		NVIC_Enable_IRQ(USART1_IRQ);
		NVIC_SetPriority_IRQ(USART1_IRQ,IRQ_Priority);
	}
	else if(USART == USART2)
	{
		NVIC_Enable_IRQ(USART2_IRQ);
		NVIC_SetPriority_IRQ(USART2_IRQ,IRQ_Priority);
	}
	else if(USART == USART3)
	{
		NVIC_Enable_IRQ(USART3_IRQ);
		NVIC_SetPriority_IRQ(USART3_IRQ,IRQ_Priority);
	}
	Enable_IRQ();
}

void USART_UnregisterEvent(USART_RegStruct *USART,uint8_t USART_Event)
{
	Disable_IRQ();
	if(USART_Event ==0)
	{
		USART->CR3 &= ~(uint32_t)(1<<0);
	}
	else if(USART_Event == 0xFF)
	{
		USART->CR1 &= ~(uint32_t)(0x01F0);
		USART->CR3 &= ~(uint32_t)(1<<0);
		if(USART == USART1)
		{
			NVIC_Disable_IRQ(USART1_IRQ);
		}
		else if(USART == USART2)
		{
			NVIC_Disable_IRQ(USART2_IRQ);
		}
		else if(USART == USART3)
		{
			NVIC_Disable_IRQ(USART3_IRQ);
		}
	}
	else
	{
		USART->CR1 &= ~(uint32_t)(1<<USART_Event);
	}
	Enable_IRQ();
}

__attribute__ ((weak)) void USART1_IRQHandler()
{
	uint8_t Event =1;
	/*Detect Event*/
	if(USART1->CR1 &(1<<USART_ReceivedData_Event))
	{
		if(USART1->SR &(1<<USART_ReceivedData_Event))
		{
			Event = USART_ReceivedData_Event;
			goto Out;
		}
	}
	if(USART1->CR1 & (1<<USART_PermitTransmit_Event))
	{
		if(USART1->SR &(1<<USART_PermitTransmit_Event))
		{
			Event = USART_PermitTransmit_Event;
			goto Out;
		}
	}
	if(USART1->CR1 & (1<<USART_TransmitComplete_Event))
	{
		if(USART1->SR &(1<<USART_TransmitComplete_Event))
		{
			Event = USART_TransmitComplete_Event;
			goto Out;
		}
	}
	if(USART1->CR1 &(1<<USART_ParityError_Event))
	{
		if(USART1->SR & (1<<0))
		{
			Event = USART_ParityError_Event;
			goto Out;
		}
	}
	if(USART1->CR1 & (1<<USART_IdleDetected_Event))
	{
		if(USART1->SR & (1<<USART_IdleDetected_Event))
		{
			Event = USART_IdleDetected_Event;
			goto Out;
		}
	}
	if(USART1->CR3 & (1<<USART_Error_Event))
	{
		if(USART1->SR & (uint32_t)0x0E)
		{
			Event = USART_Error_Event;
		}
	}
	Out:
	Handler_CallBack(Event);
}

__attribute__ ((weak)) void USART2_IRQHandler()
{
	uint8_t Event =1;
	/*Detect Event*/
	if(USART2->CR1 &(1<<USART_ReceivedData_Event))
	{
		if(USART2->SR &(1<<USART_ReceivedData_Event))
		{
			Event = USART_ReceivedData_Event;
			goto Out;
		}
	}
	if(USART2->CR1 & (1<<USART_PermitTransmit_Event))
	{
		if(USART2->SR &(1<<USART_PermitTransmit_Event))
		{
			Event = USART_PermitTransmit_Event;
			goto Out;
		}
	}
	if(USART2->CR1 & (1<<USART_TransmitComplete_Event))
	{
		if(USART2->SR &(1<<USART_TransmitComplete_Event))
		{
			Event = USART_TransmitComplete_Event;
			goto Out;
		}
	}
	if(USART2->CR1 &(1<<USART_ParityError_Event))
	{
		if(USART2->SR & (1<<0))
		{
			Event = USART_ParityError_Event;
			goto Out;
		}
	}
	if(USART2->CR1 & (1<<USART_IdleDetected_Event))
	{
		if(USART2->SR & (1<<USART_IdleDetected_Event))
		{
			Event = USART_IdleDetected_Event;
			goto Out;
		}
	}
	if(USART2->CR3 & (1<<USART_Error_Event))
	{
		if(USART2->SR & (uint32_t)0x0E)
		{
			Event = USART_Error_Event;
		}
	}
	Out:
	Handler_CallBack(Event);
}


__attribute__ ((weak)) void USART3_IRQHandler()
{
	uint8_t Event =1;
	/*Detect Event*/
	if(USART3->CR1 &(1<<USART_ReceivedData_Event))
	{
		if(USART3->SR &(1<<USART_ReceivedData_Event))
		{
			Event = USART_ReceivedData_Event;
			goto Out;
		}
	}
	if(USART3->CR1 & (1<<USART_PermitTransmit_Event))
	{
		if(USART3->SR &(1<<USART_PermitTransmit_Event))
		{
			Event = USART_PermitTransmit_Event;
			goto Out;
		}
	}
	if(USART3->CR1 & (1<<USART_TransmitComplete_Event))
	{
		if(USART3->SR &(1<<USART_TransmitComplete_Event))
		{
			Event = USART_TransmitComplete_Event;
			goto Out;
		}
	}
	if(USART3->CR1 &(1<<USART_ParityError_Event))
	{
		if(USART3->SR & (1<<0))
		{
			Event = USART_ParityError_Event;
			goto Out;
		}
	}
	if(USART3->CR1 & (1<<USART_IdleDetected_Event))
	{
		if(USART3->SR & (1<<USART_IdleDetected_Event))
		{
			Event = USART_IdleDetected_Event;
			goto Out;
		}
	}
	if(USART3->CR3 & (1<<USART_Error_Event))
	{
		if(USART3->SR & (uint32_t)0x0E)
		{
			Event = USART_Error_Event;
		}
	}
	Out:
	Handler_CallBack(Event);
}
	
