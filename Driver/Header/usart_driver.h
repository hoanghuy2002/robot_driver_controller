#ifndef _USART_DRIVER_H_
#define _USART_DRIVER_H_

#include "stm32f103.h"

/* USART Clock Control*/
#define USART1_EnableCLK()			(RCC->APB2ENR |= (uint32_t)(1<<14))
#define USART2_EnableCLK()			(RCC->APB1ENR |= (uint32_t)(1<<17))
#define USART3_EnableCLK()			(RCC->APB1ENR |= (uint32_t)(1<<18))



typedef struct
{
	USART_RegStruct *USART;
	uint8_t 	USART_Mode;
	uint8_t 	USART_WordLength;
	uint8_t 	USART_StopBit;
	uint8_t 	USART_Parity;
	uint32_t 	USART_Baudrate;
	uint8_t 	USART_HWFlowControl;
}USART_ConfigStruct;



/*
*@USART_Mode
*Possible options for USART_Mode
*/
#define USART_RX_Mode				1
#define USART_TX_Mode				2
#define USART_TXRX_Mode			3

/*
*@USART_WordLength
*Possible options for USART_WordLength
*/
#define USART_8Bit					0
#define USART_9Bit					1

/*
*@USART_StopBit
*Possible options for USART_StopBit
*/
#define USART_0_5StopBit			1
#define USART_1StopBit				0
#define USART_1_5StopBit			3
#define USART_2StopBit				2

/*
*@USART_Parity
*Possible options for USART_Parity
*/
#define USART_ParityDisable		0
#define USART_ParityEven			2
#define USART_ParityOdd				3

/*
*@USART_Baudrate
*Possible options for USART_Baudrate
*/

#define USART_Baudrate_1200					1200
#define USART_Baudrate_2400					2400
#define USART_Baudrate_9600					9600
#define USART_Baudrate_19200 				19200
#define USART_Baudrate_38400 				38400
#define USART_Baudrate_57600 				57600
#define USART_Baudrate_115200 			115200
#define USART_Baudrate_230400 			230400
#define USART_Baudrate_460800 			460800
#define USART_Baudrate_921600 			921600

/*
*@USART_HWFlowControl
*Possible options for USART_HWFlowControl
*/
#define USART_FlowControl_Disable		0
#define USART_RTS_Enable						1
#define USART_CTS_Enable						2
#define USART_RTSCTS_Enable					3


/*
*@USART_Event
*Possible options for USART_Event
*/

#define USART_ParityError_Event 				8
#define USART_PermitTransmit_Event 			7
#define USART_TransmitComplete_Event 		6
#define USART_ReceivedData_Event				5
#define USART_IdleDetected_Event				4
#define USART_Error_Event								0
#define USART_All_Event									0xFFU


/*
*Prototype of function
*/
void USART_Init(USART_ConfigStruct *USART_Config);
void USART_WriteData(USART_RegStruct *USART, uint8_t *Buffer,uint8_t Buffer_Length);
void USART_ReadData(USART_RegStruct *USART, uint8_t *Buffer);
void USART_RegisterEvent(USART_RegStruct *USART,uint8_t USART_Event,void (*Event_Handler)(uint8_t));
void USART_UnregisterEvent(USART_RegStruct *USART,uint8_t USART_Event);
void USART1_IRQHandler(void);
void USART2_IRQHandler(void);
void USART3_IRQHandler(void);
#endif

