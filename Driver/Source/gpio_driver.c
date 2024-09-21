#include "gpio_driver.h"
#include "cortexm3_irq.h"

/*********************************************************************
 * @fn      		  - GPIO_ClockControl
 *
 * @brief             - This function enables or disables peripheral clock for the given GPIO port
 *
 * @param[in]         - base address of the gpio peripheral
 * @param[in]         - ENABLE or DISABLE from DisEn_t enum
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void GPIO_ClockControl(GPIO_RegStruct *GPIO_PORT,uint8_t DisorEn)
{
    if (DisorEn == Enable)
    {
			if(GPIO_PORT == GPIOA)
			{
				GPIOA_EnableCLK();
			}
			else if(GPIO_PORT == GPIOB)
			{
				GPIOB_EnableCLK();
			}
			else if(GPIO_PORT == GPIOC)
			{
				GPIOC_EnableCLK();
			}
    }
    else if (DisorEn == Disable)
    {
      if(GPIO_PORT == GPIOA)
			{
				GPIOA_DisableCLK();
			}
			else if(GPIO_PORT == GPIOB)
			{
				GPIOB_DisableCLK();
			}
			else if(GPIO_PORT == GPIOC)
			{
				GPIOC_DisableCLK();
			}
    }
}


/*********************************************************************
 * @fn      		  		- GPIO_Init
 *
 * @brief             - This function Config Input/Output Direction and Mode
 *
 * @param[in]         - Structure Config Address GPIO Port, Pin, Direction and Mode
 *
 * @return            -  none
 *
 * @Note              -  none

 */


void GPIO_Init(GPIO_ConfigStruct *GPIO_Config)
{
		GPIO_ClockControl(GPIO_Config->GPIO_PORT,Enable);
    uint8_t Pin = (uint8_t) GPIO_Config->GPIO_PinNumber;
    if (Pin<8)
    {
        GPIO_Config->GPIO_PORT->CRL &= ~(uint32_t)(0x0F<<(Pin*4));
        GPIO_Config->GPIO_PORT->CRL |= (uint32_t)(GPIO_Config->GPIO_Direction<<Pin*4)
                                                 |(uint32_t)(GPIO_Config->GPIO_Mode<<(Pin*4+2));
    }
    else
    {
        Pin -=8;
        GPIO_Config->GPIO_PORT->CRH &= ~(uint32_t)(0x0F<<(Pin*4));
        GPIO_Config->GPIO_PORT->CRH |= (uint32_t)(GPIO_Config->GPIO_Direction<<Pin*4)
                                                 |(uint32_t)(GPIO_Config->GPIO_Mode<<(Pin*4+2));
    }
}

void GPIO_SetMode(GPIO_RegStruct *Port,uint8_t GPIO_PinNumber,uint8_t GPIO_Direction, uint8_t GPIO_Mode)
{
	GPIO_ClockControl(Port,Enable);
	uint8_t Pin = (uint8_t) GPIO_PinNumber;
    if (Pin<8)
    {
        Port->CRL &= ~(uint32_t)(0x0F<<(Pin*4));
        Port->CRL |= (uint32_t)(GPIO_Direction<<Pin*4)|(uint32_t)(GPIO_Mode<<(Pin*4+2));
    }
    else
    {
        Pin -=8;
        Port->CRH &= ~(uint32_t)(0x0F<<(Pin*4));
        Port->CRH |= (uint32_t)(GPIO_Direction<<Pin*4)|(uint32_t)(GPIO_Mode<<(Pin*4+2));
    }
}


/*********************************************************************
 * @fn      		  		- GPIO_WritePin
 *
 * @brief             - This function Set/Reset GPIO_Pin
 *
 * @param[1]          - GPIO Port
 * @param[2]          - GPIO Pin
 * @param[3]          - Level: High/Low
 *
 * @return            -  none
 *
 * @Note              -  none

 */


void GPIO_WritePin(GPIO_RegStruct *GPIO_PORT,uint8_t GPIO_PinNumber,uint8_t GPIO_Level)
{
	if(GPIO_Level == GPIO_Low)
	{
		GPIO_PORT->ODR &= ~(uint32_t)(1<<GPIO_PinNumber);
	}
	else if(GPIO_Level == GPIO_High)
	{
		GPIO_PORT->ODR |= (uint32_t)(1<<GPIO_PinNumber);
	}
}

/*********************************************************************
 * @fn      		  		- GPIO_WritePort
 *
 * @brief             - This function Set/Reset All the Pin of GPIO Port
 *
 * @param[1]          - GPIO Port
 * @param[2]          - GPIO PIN
 * @param[3]          - Level: High/Low
 *
 * @return            -  none
 *
 * @Note              -  none

 */

void GPIO_WritePort(GPIO_RegStruct *GPIO_PORT,uint8_t GPIO_Level)
{
	GPIO_PORT->ODR = (uint32_t)(0x0F*GPIO_Level);
}


/*********************************************************************
 * @fn      		  		- GPIO_ReadPin
 *
 * @brief             - This function Read the level Of GPIO_Pin
 *
 * @param[1]          - GPIO Port
 * @param[3]          - Level: High/Low
 *
 * @return            -  Level Pin: High/Low
 *
 * @Note              -  none

 */


uint8_t GPIO_ReadPin(GPIO_RegStruct *GPIO_PORT,uint8_t GPIO_PinNumber)
{
	uint8_t Level_Pin = (uint8_t)((GPIO_PORT->IDR&(1<<GPIO_PinNumber))>>GPIO_PinNumber);
	return Level_Pin;
}

void GPIO_IRQ_Enable(EXTI_PORT_t Port,uint8_t GPIO_PinNumber, uint8_t GPIO_Edge)
{
	uint8_t IRQ_Number;
	Disable_IRQ();
	AFIO->EXTICR[GPIO_PinNumber/4] &= ~(uint32_t)(Port<<GPIO_PinNumber*4);
	AFIO->EXTICR[GPIO_PinNumber/4] |= (uint32_t)(Port<<GPIO_PinNumber*4);
	EXTI->IMR |= (uint32_t)(1<<GPIO_PinNumber);
	if (GPIO_Edge == GPIO_FallingEdge)
	{
		EXTI->FTSR |= (1<<GPIO_PinNumber);
	}
	else if(GPIO_Edge == GPIO_RisingEdge)
	{
		EXTI->RTSR |= (1<<GPIO_PinNumber);
	}
	if(GPIO_PinNumber < 5)
	{
		IRQ_Number = 6 + GPIO_PinNumber;
	}
	else if(GPIO_PinNumber < 10)
	{
		IRQ_Number = 23;
	}
	else 
	{
		IRQ_Number = 40;
	}
	NVIC_Enable_IRQ(IRQ_Number);
	Enable_IRQ();
}


void GPIO_IRQ_Disable(EXTI_PORT_t Port,uint8_t GPIO_PinNumber)
{
	uint8_t IRQ_Number;
	Disable_IRQ();
	AFIO->EXTICR[GPIO_PinNumber/4] &= ~(uint32_t)(Port<<GPIO_PinNumber*4);
	EXTI->IMR &= ~(uint32_t)(1<<GPIO_PinNumber);
	EXTI->FTSR &= ~(1<<GPIO_PinNumber);
	EXTI->RTSR &= ~(1<<GPIO_PinNumber);
	if(GPIO_PinNumber < 5)
	{
		IRQ_Number = 6 + GPIO_PinNumber;
	}
	else if(GPIO_PinNumber < 10)
	{
		IRQ_Number = 23;
	}
	else 
	{
		IRQ_Number = 40;
	}
	NVIC_Disable_IRQ(IRQ_Number);
	Enable_IRQ();
}

void GPIO_ResetPending(uint8_t GPIO_PinNumber)
{
	EXTI->PR |= (uint32_t)(1<<GPIO_PinNumber);
}

