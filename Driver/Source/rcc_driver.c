#include "stm32f103.h"
#include "rcc_driver.h"

#define SystemCLK_72MHz
#define USB_NotPreScaler
#define ADC_PreScaler_2
#define APB2_PreScaler_2
#define APB1_PreScaler_2

static void SysCLK_PreScaler(void);

inline static uint8_t SetPLLCLK_HSE(uint8_t PLL_Multiple)
{
	uint16_t count =0;
	RCC->CR |= (1<<16);														/*HSE On*/
	while((RCC->CR & (1<<17)) ==0);								/*Wait for HSE Ready*/
	RCC->CFGR |= (1<<16);													/*PLL Select HSE Clock is Input*/
	RCC->CFGR |= (uint32_t)(PLL_Multiple<<18);								/*PLL Multilple*/
	RCC->CR |= (1<<24);														/*PLL On*/
	count =0;
	while((RCC->CR & (1<<25)) == 0);
	return 1;
}


inline static void SetSysCLK(void)
{
	
/* System Clock Configuration*/
#ifdef SystemCLK_72MHz
	if (SetPLLCLK_HSE(7) ==0) return;
	#define SysCLK  72000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (2<<0);
#elif defined SystemCLK_64MHz
	if (SetPLLCLK_HSE(6) ==0) return;
	#define SysCLK  64000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (2<<0);
#elif defined SystemCLK_56MHz
	if (SetPLLCLK_HSE(5) ==0) return;
	#define SysCLK  56000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (2<<0);
#elif defined SystemCLK_48MHz
	if (SetPLLCLK_HSE(4) ==0) return;
	#define SysCLK  48000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (1<<0);
#elif defined SystemCLK_40MHz
	if (SetPLLCLK_HSE(3) ==0) return;
	#define SysCLK  40000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (1<<0);
#elif defined SystemCLK_32MHz
	if (SetPLLCLK_HSE(2) ==0) return;
	#define SysCLK  32000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (1<<0);
#elif defined SystemCLK_24MHz
	if (SetPLLCLK_HSE(1) ==0) return;
	#define SysCLK  24000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (0<<0);
#elif defined SystemCLK_16MHz
	if (SetPLLCLK_HSE(0) ==0) return;
	#define SysCLK  16000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (0<<0);
#else
	#define SysCLK  8000000U
	FLASH->ACR |= (1<<4);
	FLASH->ACR |= (0<<0);
	return;
#endif
SysCLK_PreScaler();
RCC->CFGR |= (2<<0);
while((RCC->CFGR &(2<<2)) ==0);

}

static void SysCLK_PreScaler(void)
{
#ifdef AHB_PreScaler_2
	RCC->CFGR |= (8<<4);
	#define HCLK SysCLK/2
#elif defined AHB_PreScaler_4
	RCC->CFGR |= (9<<4
	#define HCLK SysCLK/4
#elif defined AHB_PreScaler_8
	RCC->CFGR |= (10<<4);
	#define HCLK SysCLK/8
#elif defined AHB_PreScaler_16
	RCC->CFGR |= (11<<4);
	#define HCLK SysCLK/16
#elif defined AHB_PreScaler_64
	RCC->CFGR |= (12<<4);
	#define HCLK SysCLK/64
#elif defined AHB_PreScaler_128
	RCC->CFGR |= (13<<4);
	#define HCLK SysCLK/128
#elif defined AHB_PreScaler_256
	RCC->CFGR |= (14<<4);
	#define HCLK SysCLK/256
#elif defined AHB_PreScaler_512
	RCC->CFGR |= (15<<4);
	#define HCLK SysCLK/512
#else 
	#define HCLK (uint32_t)SysCLK
#endif
	
#ifdef APB1_PreScaler_2
	RCC->CFGR |= (4<<8);
	#define APB1CLK HCLK/2
#elif defined APB1_PreScaler_4
	RCC->CFGR	|= (5<<8);
	#define APB1CLK HCLK/4
#elif defined APB1_PreScaler_8
	RCC->CFGR |= (6<<8);
	#define APB1CLK HCLK/8
#elif defined APB1_PreScaler_16
	RCC->CFGR |= (7<<8);
	#define APB1CLK HCLK/16
#else 
	#define APB1CLK HCLK
#endif
	
#ifdef	APB2_PreScaler_2
	RCC->CFGR |= (4<<11);
	#define APB2CLK HCLK/2
#elif defined APB2_PreScaler_4
	RCC->CFGR	|= (5<<11);
	#define APB2CLK HCLK/4
#elif defined APB2_PreScaler_8
	RCC->CFGR |= (6<<11);
	#define APB2CLK HCLK/8
#elif defined APB2_PreScaler_16
	RCC->CFGR |= (7<<11);
	#define APB2CLK HCLK/16
#else 
	#define APB2CLK HCLK
#endif

#ifdef USB_NotPreScaler
	RCC->CFGR |= (1<<22);
	#define USBCLK SysCLK
#else 
	#define USBCLK SysCLK/1.5
#endif
 	
#ifdef ADC_PreScaler_2
	RCC->CFGR |= (1<<14);
	#define ADCCLK APB2CLK/2
#elif defined ADC_PreScaler_4
	RCC->CFGR |= (2<<14);
	#define ADCCLK APB2CLK/4
#elif defined ADC_PreScaler_8
	RCC->CFGR |= (3<<14);
	#define ADCCLK APB2CLK/8
#else
	#define ADCCLK APB2CLK
#endif
	


}

void System_Init(void)
{
	SetSysCLK();
}

uint32_t GetAHB_Clock(void)
{
	return HCLK;
}

uint32_t GetAPB1_Clock(void)
{
	return APB1CLK;
}

uint32_t GetAPB2_Clock(void)
{
	return APB2CLK;
}

uint32_t GetADC_Clock(void)
{
	return ADCCLK;
}

uint32_t GetUSB_Clock(void)
{
	return USBCLK;
}

uint32_t GetTimer_Clock(TIM_RegStruct *TIM)
{
	if(TIM == TIM1 || TIM == TIM8 || TIM == TIM9 || TIM == TIM10 || TIM == TIM11)
	{
		#ifdef APB2_PreScaler_1
			return APB2CLK
		#else
			return 2*APB2CLK;
		#endif
	}
	else
	{
		#ifdef APB1_PreScaler_1
			return APB2CLK
		#else
			return 2*APB1CLK;
		#endif
	}
}






