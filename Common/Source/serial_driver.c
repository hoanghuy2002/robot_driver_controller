#include "serial_driver.h"
#include "usart_driver.h"
#include "gpio_driver.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define Serial_USART                USART1
#define Serial_Mode                 USART_TXRX_Mode
#define Serial_Number_Data_Bit      USART_8Bit
#define Serial_Number_Stop_Bit      USART_1StopBit
#define Serial_Parity               USART_ParityDisable
#define Serial_Baudrate             USART_Baudrate_57600
#define Serial_Flow_Control         USART_FlowControl_Disable

#define Serial_TX_GPIO_Port         GPIOA
#define Serial_TX_GPIO_Pin          GPIO_Pin9
#define Serial_RX_GPIO_Port         GPIOA
#define Serial_RX_GPIO_Pin          GPIO_Pin10

typedef void(*Function_Callback)(void);
Function_Callback Handler_Callback;
char *Buffer_Received = NULL;

static void USART_Receive_Data_Handler(uint8_t Event)
{
    static uint8_t Index_Buffer = 0;
    USART_ReadData(Serial_USART,(uint8_t *)(Buffer_Received+Index_Buffer));
    if (*(Buffer_Received + Index_Buffer) == NULL)      // == "\n"
    {
        // Serial_Write(Buffer_Received);
        Handler_Callback();
        for (uint8_t i =0; i<=Index_Buffer;i++)
        {
            *(Buffer_Received + i) =NULL;
        }
        Index_Buffer =0;
    }
    else
    {
        Index_Buffer ++;
    }
    
}

void Serial_Initialization(void (*Even_Handler)(void))
{
    USART_ConfigStruct Serial_Configuration;
    Serial_Configuration.USART = Serial_USART;
    Serial_Configuration.USART_Mode = Serial_Mode;
    Serial_Configuration.USART_WordLength = Serial_Number_Data_Bit;
    Serial_Configuration.USART_StopBit = Serial_Number_Stop_Bit;
    Serial_Configuration.USART_Parity = Serial_Parity;
    Serial_Configuration.USART_Baudrate = Serial_Baudrate;
    Serial_Configuration.USART_HWFlowControl = Serial_Flow_Control;
    USART_Init(&Serial_Configuration);
    Buffer_Received = (char *)calloc(64,sizeof(char));
    USART_RegisterEvent(Serial_USART,USART_ReceivedData_Event,3,&USART_Receive_Data_Handler);
    Handler_Callback = Even_Handler;
    

}

void Serial_Write(char *String)
{
        USART_WriteData(Serial_USART,(uint8_t *)String,strlen(String));
}

char *Serial_Read(void)
{
    return Buffer_Received;
}




