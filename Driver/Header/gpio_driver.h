#ifndef _DRIVER_H_
#define _DRIVER_H_

#include "stm32f103.h"


//// GPIO Clock Control

#define AFIO_EnableCLK()     (RCC->APB2ENR|=(uint32_t)(1<<0))
#define GPIOA_EnableCLK()    (RCC->APB2ENR|=(uint32_t)(1<<2))
#define GPIOB_EnableCLK()    (RCC->APB2ENR|=(uint32_t)(1<<3))
#define GPIOC_EnableCLK()    (RCC->APB2ENR|=(uint32_t)(1<<4))



#define AFIO_DisableCLK()    (RCC->APB2ENR&= ~(uint32_t)(1<<0))
#define GPIOA_DisableCLK()   (RCC->APB2ENR&= ~(uint32_t)(1<<2))
#define GPIOB_DisableCLK()   (RCC->APB2ENR&= ~(uint32_t)(1<<3))
#define GPIOC_DisableCLK()   (RCC->APB2ENR&= ~(uint32_t)(1<<4))



typedef enum
{
	EXTI_PORTA,
	EXTI_PORTB,
	EXTI_PORTC,
}EXTI_PORT_t;

typedef struct
{
    GPIO_RegStruct *GPIO_PORT;
		uint8_t GPIO_PinNumber;
    uint8_t GPIO_Direction;
    uint8_t GPIO_Mode;
}GPIO_ConfigStruct;





//// Function

void GPIO_ClockControl(GPIO_RegStruct *GPIO_PORT,uint8_t DisorEn);
void GPIO_Init(GPIO_ConfigStruct *GPIO_Config);
void GPIO_SetMode(GPIO_RegStruct *Port,uint8_t GPIO_PinNumber,uint8_t GPIO_Direction, uint8_t GPIO_Mode);
void GPIO_WritePin(GPIO_RegStruct *GPIO_PORT,uint8_t GPIO_PinNumber,uint8_t GPIO_Level);
void GPIO_WritePort(GPIO_RegStruct *GPIO_PORT,uint8_t GPIO_Level);
uint8_t GPIO_ReadPin(GPIO_RegStruct *GPIO_PORT,uint8_t GPIO_PinNumber);
void GPIO_IRQ_Enable(EXTI_PORT_t Port,uint8_t GPIO_PinNumber, uint8_t GPIO_Edge);
void GPIO_IRQ_Disable(EXTI_PORT_t Port,uint8_t GPIO_PinNumber);
void GPIO_ResetPending(uint8_t GPIO_PinNumber);
//// IRQ_Handler
void EXTI0_IRQHandler(void);
void EXTI1_IRQHandler(void);
void EXTI2_IRQHandler(void);
void EXTI3_IRQHandler(void);
void EXTI4_IRQHandler(void);
void EXTI9_5_IRQHandler(void);
void EXTI15_10_IRQHandler(void);



/*Possible Parameters for Functions and Structs of GPIO*/

/*GPIO_PinNumber*/
#define GPIO_Pin0						0U
#define GPIO_Pin1						1U
#define GPIO_Pin2						2U
#define GPIO_Pin3						3U
#define GPIO_Pin4						4U	
#define GPIO_Pin5						5U
#define GPIO_Pin6						6U
#define GPIO_Pin7						7U
#define GPIO_Pin8						8U
#define GPIO_Pin9						9U
#define GPIO_Pin10					10U
#define GPIO_Pin11					11U
#define GPIO_Pin12					12U
#define GPIO_Pin13					13U
#define GPIO_Pin14					14U
#define GPIO_Pin15					15U

/*GPIO_Direction*/
#define GPIO_Input					0U
#define GPIO_Output_10MHz		1U
#define GPIO_Output_2MHz		2U
#define GPIO_Output_50MHz		3U

/*GPIO_Mode*/
#define GPIO_IP_Analog			0U    /*Input with Mode Analog*/
#define GPIO_IP_Floating		1U		/*Input with Mode Floating*/
#define GPIO_IP_PUPD				2U		/*Input with Mode Pullup-Pulldown*/
#define GPIO_OP_GPPP				0U		/*Output with Mode General Purpose Push-Pull*/  
#define GPIO_OP_GPOD				1U		/*Output with Mode General Purpose Open-Drain*/
#define GPIO_OP_AFPP				2U		/*Output with Mode Alternate Function Push-Pull*/
#define GPIO_OP_AFOD				3U		/*Output with Mode Alternate Function Open-Drain*/

/*GPIO_Level*/
#define GPIO_Low						0U
#define GPIO_High						1U

/*GPIO_Edge*/
#define GPIO_FallingEdge				0U
#define GPIO_RisingEdge					1U

/*DisorEn*/
#define Disable									0U
#define Enable									1U

#endif

