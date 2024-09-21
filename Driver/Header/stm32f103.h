#ifndef _STM32F103_H_
#define _STM32F103_H_

#include <stdint.h>
#include "cortexm3.h"
#include "cortexm3_irq.h"

#define FLASH_BASEADDR      (0x08000000U)
#define SRAM_BASEADDR       (0x20000000U)
#define ROM_BASEADDR        (0x1FFFF000U)

#define APB1_BASEADDR       (0x40000000U)
#define APB2_BASEADDR       (0x40010000U)
#define AHB_BASEADDR        (0x40018000U)





/// APB1 Peripherals Address
#define TIM2_BASEADDR						(APB1_BASEADDR+0x0000)
#define TIM3_BASEADDR						(APB1_BASEADDR+0x0400)
#define TIM4_BASEADDR						(APB1_BASEADDR+0x0800)
#define TIM5_BASEADDR						(APB1_BASEADDR+0x0C00)
#define TIM6_BASEADDR						(APB1_BASEADDR+0x1000)
#define TIM7_BASEADDR						(APB1_BASEADDR+0x1400)
#define TIM12_BASEADDR					(APB1_BASEADDR+0x1800)
#define TIM13_BASEADDR					(APB1_BASEADDR+0x1C00)
#define TIM14_BASEADDR					(APB1_BASEADDR+0x2000)
#define SPI2_BASEADDR						(APB1_BASEADDR+0x3800)
#define SPI3_BASEADDR						(APB1_BASEADDR+0X3C00)
#define USART2_BASEADDR					(APB1_BASEADDR+0x4400)
#define USART3_BASEADDR					(APB1_BASEADDR+0x4800)
#define UART4_BASEADDR					(APB1_BASEADDR+0x4C00)
#define UART5_BASEADDR					(APB1_BASEADDR+0x5000)
#define I2C1_BASEADDR						(APB1_BASEADDR+0x5400)
#define I2C2_BASEADDR						(APB1_BASEADDR+0x5800)
#define CAN1_BASEADDR						(APB1_BASEADDR+0x6400)
#define CAN2_BASEADDR						(APB1_BASEADDR+0x6800)

/// APB2 Peripherals Address
#define AFIO_BASEADDR           (APB2_BASEADDR+0x0)
#define EXTI_BASEADDR           (APB2_BASEADDR+0x0400)
#define GPIOA_BASEADDR          (APB2_BASEADDR+0x0800)
#define GPIOB_BASEADDR          (APB2_BASEADDR+0x0C00)
#define GPIOC_BASEADDR          (APB2_BASEADDR+0x1000)
#define ADC1_BASEADDR						(APB2_BASEADDR+0x2400)
#define ADC2_BASEADDR						(APB2_BASEADDR+0x2800)
#define TIM1_BASEADDR						(APB2_BASEADDR+0x2C00)
#define SPI1_BASEADDR						(APB2_BASEADDR+0x3000)
#define TIM8_BASEADDR						(APB2_BASEADDR+0x3400)
#define USART1_BASEADDR					(APB2_BASEADDR+0x3800)
#define ADC3_BASEADDR						(APB2_BASEADDR+0x3C00)
#define TIM9_BASEADDR						(APB2_BASEADDR+0x4C00)
#define TIM10_BASEADDR					(APB2_BASEADDR+0x5000)
#define TIM11_BASEADDR					(APB2_BASEADDR+0x5400)


/// AHB Peripherals Address
#define RCC_BASEADDR        					(AHB_BASEADDR+0x9000)
#define FLASH_INTERFACE_BASEADDR			(AHB_BASEADDR+0xA000)

////
/**/
/**/
/**/

typedef struct
{
	volatile uint32_t ACR;
}FLASH_RegStruct;

/*************************/

typedef struct 
{
    volatile uint32_t CR;
		volatile uint32_t CFGR;
		volatile uint32_t CIR;
		volatile uint32_t APB2RSTR;
		volatile uint32_t APB1RSTR;
		volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
    volatile uint32_t APB1ENR;
		volatile uint32_t BDCR;
}RCC_RegStruct;

/*************************/

typedef struct{
	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
	volatile uint32_t LCKR;
}GPIO_RegStruct;

/*************************/

typedef struct 
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_RegStruct;

/*************************/

typedef struct 
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR[4];
	volatile uint32_t MAPR2; 
}AFIO_RegStruct;

/*************************/

typedef struct
{
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR[2];
	volatile uint32_t JOFR[4];
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR[3];
	volatile uint32_t JSQR;
	volatile uint32_t JDR[4];
	volatile uint32_t DR;
}ADC_RegStruct;

/*************************/

typedef struct{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	volatile uint32_t RCR;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	volatile uint32_t BDTR;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
}TIM_RegStruct;


/*************************/

typedef struct
{
	volatile uint32_t TIR;
	volatile uint32_t TDTR;
	volatile uint32_t TDLR;
	volatile uint32_t TDHR;
}CAN_TransmitMailBoxStruct;

typedef struct
{
	volatile uint32_t RIR;
	volatile uint32_t RDTR;
	volatile uint32_t RDLR;
	volatile uint32_t RDHR;
}CAN_ReceiveMailBoxStruct;

typedef struct
{
	volatile uint32_t FR0;
	volatile uint32_t FR1;
}CAN_FillterBankStruct;

typedef struct
{
	volatile uint32_t MCR;
	volatile uint32_t MSR;
	volatile uint32_t TSR;
	volatile uint32_t RF0R;
	volatile uint32_t RF1R;
	volatile uint32_t IER;
	volatile uint32_t ESR;
	volatile uint32_t BTR;
	volatile uint32_t Reserved0[88];
	CAN_TransmitMailBoxStruct TXMailBox[3];						/*MailBox 0 - MailBox 1 - MailBox 0*/
	CAN_ReceiveMailBoxStruct  RXMailBox[2];						/*Receive MailBox of FIFO 0 - Receive MailBox of FIFO 1*/
	volatile uint32_t Reserved1[12];
	volatile uint32_t FMR;
	volatile uint32_t FM1R;
	volatile uint32_t Reserved2;
	volatile uint32_t FS1R;
	volatile uint32_t Reserved3;
	volatile uint32_t FFA1R;
	volatile uint32_t Reserved4;
	volatile uint32_t FA1R;
	volatile uint32_t Reserved5[8];
	CAN_FillterBankStruct FillterBank[28]; 
}CAN_RegStruct;

/*************************/

typedef struct
{
		volatile uint32_t CR1;
		volatile uint32_t CR2;
		volatile uint32_t SR;
		volatile uint32_t DR;
		volatile uint32_t CRCPR;
		volatile uint32_t RXCRCR;
		volatile uint32_t TXCRCR;
		volatile uint32_t I2SCFGR;
		volatile uint32_t I2SPR;
}SPI_RegStruct;

/*************************/

typedef struct
{
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
}I2C_RegStruct;

/*************************/

typedef struct
{
		volatile uint32_t SR;
		volatile uint32_t DR;
		volatile uint32_t BRR;
		volatile uint32_t CR1;
		volatile uint32_t CR2;
		volatile uint32_t CR3;
		volatile uint32_t GTPR;
}USART_RegStruct;


/*************************/
/*************************/
/*************************/
/*************************/

/*APB1 Peripherals Registers Structure*/

#define TIM2									((TIM_RegStruct*)TIM2_BASEADDR)
#define TIM3									((TIM_RegStruct*)TIM3_BASEADDR)
#define TIM4									((TIM_RegStruct*)TIM4_BASEADDR)
#define TIM5									((TIM_RegStruct*)TIM5_BASEADDR)
#define TIM6									((TIM_RegStruct*)TIM6_BASEADDR)
#define TIM7									((TIM_RegStruct*)TIM7_BASEADDR)
#define TIM12									((TIM_RegStruct*)TIM12_BASEADDR)
#define TIM13									((TIM_RegStruct*)TIM13_BASEADDR)
#define TIM14									((TIM_RegStruct*)TIM14_BASEADDR)
#define SPI2 									((SPI_RegStruct*)SPI2_BASEADDR)
#define SPI3 									((SPI_RegStruct*)SPI3_BASEADDR)
#define USART2								((USART_RegStruct*)USART2_BASEADDR)
#define USART3								((USART_RegStruct*)USART3_BASEADDR)
#define UART4									((USART_RegStruct*)UART4_BASEADDR)
#define UART5									((USART_RegStruct*)UART5_BASEADDR)
#define I2C1									((I2C_RegStruct*)I2C1_BASEADDR)
#define I2C2									((I2C_RegStruct*)I2C2_BASEADDR)
#define CAN1									((CAN_RegStruct*)CAN1_BASEADDR)
#define CAN2									((CAN_RegStruct*)CAN2_BASEADDR)

/*************************/

/*APB2 Peripherals Registers Structure*/

#define AFIO    							((AFIO_RegStruct*)AFIO_BASEADDR)
#define EXTI    							((EXTI_RegStruct*)EXTI_BASEADDR)
#define GPIOA   							((GPIO_RegStruct*)GPIOA_BASEADDR)
#define GPIOB   							((GPIO_RegStruct*)GPIOB_BASEADDR)
#define GPIOC   							((GPIO_RegStruct*)GPIOC_BASEADDR)
#define ADC1									((ADC_RegStruct*)ADC1_BASEADDR)
#define ADC2									((ADC_RegStruct*)ADC2_BASEADDR)
#define TIM1									((TIM_RegStruct*)TIM1_BASEADDR)
#define SPI1 									((SPI_RegStruct*)SPI1_BASEADDR)
#define TIM8									((TIM_RegStruct*)TIM8_BASEADDR)
#define USART1								((USART_RegStruct*)USART1_BASEADDR)
#define ADC3									((ADC_RegStruct*)ADC3_BASEADDR)
#define TIM9									((TIM_RegStruct*)TIM9_BASEADDR)
#define TIM10									((TIM_RegStruct*)TIM10_BASEADDR)
#define TIM11									((TIM_RegStruct*)TIM11_BASEADDR)

/*************************/

/*AHB Peripherals Registers Structure*/

#define RCC  ((RCC_RegStruct *)RCC_BASEADDR)
#define FLASH ((FLASH_RegStruct *)FLASH_INTERFACE_BASEADDR)




/// List of Param usually used

#define Enable 			1U
#define Disable 		0U
#define null 				/0

#endif

