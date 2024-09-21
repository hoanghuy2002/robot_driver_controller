#ifndef _CORTEXM3_H
#define _CORTEXM3_H
#include <stdint.h>

typedef struct
{
	volatile uint32_t ControlStatus_Register;
	volatile uint32_t ReloadValue_Register;
	volatile uint32_t CurrentValue_Register;
	volatile uint32_t CalibValue_Register;
}SYSTICK_RegStruct;

typedef struct 
{
    volatile uint32_t SetEnable_IRQ[8u];
    volatile uint32_t Reserved0[24u];
    volatile uint32_t ClearEnable_IRQ[8u];
		volatile uint32_t Reserved1[24u];
    volatile uint32_t SetPending_IRQ[8u];
    volatile uint32_t Reserved2[24u];
    volatile uint32_t ClearPending_IRQ[8u];
    volatile uint32_t Reserved3[24u];
    volatile uint32_t ActiveBit[8u];
    volatile uint32_t Reserved4[56u];
    volatile uint8_t  IRQPriority[240u];
}NVIC_RegStruct;



#define SYSTICK ((SYSTICK_RegStruct *)0xE000E010)
#define NVIC ((NVIC_RegStruct *)0xE000E100)


/*define_IRQ Number*/
#define WWDG_IRQ            0U
#define PVD_IRQ             1U
#define TAMPER_IRQ          2U
#define RTC_IRQ             3U
#define FLASH_IRQ           4U
#define RCC_IRQ             5U
#define EXTI0_IRQ           6U
#define EXTI1_IRQ           7U
#define EXTI2_IRQ           8U
#define EXTI3_IRQ           9U
#define EXTI4_IRQ           10U
#define DMA1_Channel1_IRQ   11U
#define DMA1_Channel2_IRQ   12U
#define DMA1_Channel3_IRQ   13U
#define DMA1_Channel4_IRQ   14U
#define DMA1_Channel5_IRQ   15U
#define DMA1_Channel6_IRQ   16U
#define DMA1_Channel7_IRQ   17U
#define ADC1_2_IRQ          18U
#define CAN1_TX_IRQ         19U
#define CAN1_RX0_IRQ        20U
#define CAN1_RX1_IRQ        21U
#define CAN1_SCE_IRQ        22U
#define EXTI9_5_IRQ         23U
#define TIM1_BRK_IRQ        24U
#define TIM1_UP_IRQ         25U
#define TIM1_TRG_COM_IRQ    26U
#define TIM1_CC_IRQ         27U
#define TIM2_IRQ            28U
#define TIM3_IRQ            29U
#define TIM4_IRQ            30U
#define I2C1_EV_IRQ         31U
#define I2C1_ER_IRQ         32U
#define I2C2_EV_IRQ         33U
#define I2C2_ER_IRQ         34U
#define SPI1_IRQ            35U
#define SPI2_IRQ            36U
#define USART1_IRQ 	        37U
#define USART2_IRQ          38U
#define USART3_IRQ          39U
#define EXTI15_10_IRQ       40U
#define RTCAlarm_IRQ        41U
#define OTG_FS_WKUP_IRQ     42U
#define TIM5_IRQ            50U
#define SPI3_IRQ            51U



#endif

