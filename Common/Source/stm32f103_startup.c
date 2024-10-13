#include <stdint.h>

#define SRAM_START 0x20000000U
#define SRAM_SIZE  (18U * 1024U) ///20KB
#define SRAM_END   ((SRAM_START)+(SRAM_SIZE))
#define STACK_START SRAM_END

extern uint32_t _data_from_flash;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

int main(void);
void System_Init(void);

void __libc_init_array(void);

void Reset_Handler(void);
void DeFault_Handler(void);
void IRQ_Handler(void);

void NMI_Handler                    (void)__attribute__((weak,alias("DeFault_Handler")));
void HardFault_Handler              (void)__attribute__((weak,alias("DeFault_Handler")));
void MemManage_Handler              (void)__attribute__((weak,alias("DeFault_Handler")));
void BusFault_Handler               (void)__attribute__((weak,alias("DeFault_Handler")));
void UsageFault_Handler             (void)__attribute__((weak,alias("DeFault_Handler")));
void SVCALL_Handler                 (void)__attribute__((weak,alias("DeFault_Handler")));
void DebugMonitor_Handler           (void)__attribute__((weak,alias("DeFault_Handler")));
void PendSV_Handler                 (void)__attribute__((weak,alias("IRQ_Handler")));
void SysTick_Handler                (void)__attribute__((weak,alias("IRQ_Handler")));
void WWDG_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void PVD_IRQHandler                 (void)__attribute__((weak,alias("IRQ_Handler")));
void TAMPER_IRQHandler              (void)__attribute__((weak,alias("IRQ_Handler")));
void RTC_IRQHandler                 (void)__attribute__((weak,alias("IRQ_Handler")));
void FLASH_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void RCC_IRQHandler                 (void)__attribute__((weak,alias("IRQ_Handler")));
void EXTI0_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void EXTI1_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void EXTI2_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void EXTI3_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void EXTI4_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA1_Channel1_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA1_Channel2_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA1_Channel3_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA1_Channel4_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA1_Channel5_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA1_Channel6_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA1_Channel7_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void ADC1_ADC2_IRQHandler           (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN1_TX_IRQHandler             (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN1_RX0_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN1_RX1_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN1_SCE_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void EXTI9_5_IRQHandler             (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM1_BRK_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM1_UP_IRQHandler             (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM1_TRG_COM_IRQHandler        (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM1_CC_IRQHandler             (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM2_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM3_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM4_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void I2C1_Event_IRQHandler          (void)__attribute__((weak,alias("IRQ_Handler")));
void I2C1_Error_IRQHandler          (void)__attribute__((weak,alias("IRQ_Handler")));
void I2C2_Event_IRQHandler          (void)__attribute__((weak,alias("IRQ_Handler")));
void I2C2_Error_IRQHandler          (void)__attribute__((weak,alias("IRQ_Handler")));
void SPI1_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void SPI2_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void USART1_IRQHandler              (void)__attribute__((weak,alias("IRQ_Handler")));
void USART2_IRQHandler              (void)__attribute__((weak,alias("IRQ_Handler")));
void USART3_IRQHandler              (void)__attribute__((weak,alias("IRQ_Handler")));
void EXTI15_10_IRQHandler           (void)__attribute__((weak,alias("IRQ_Handler")));
void RTCAlarm_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void USBWakeUp_IRQHandler           (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM5_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void SPI3_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void UART4_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void UART5_IRQHandler               (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM6_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void TIM7_IRQHandler                (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA2_Channel1_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA2_Channel2_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA2_Channel3_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA2_Channel4_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void DMA2_Channel5_IRQHandler       (void)__attribute__((weak,alias("IRQ_Handler")));
void Ethernet_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void Ethernet_WAKEUP_IRQHandler     (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN2_TX_IRQHandler             (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN2_RX0_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN2_RX1_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void CAN2_SCE_IRQHandler            (void)__attribute__((weak,alias("IRQ_Handler")));
void OTG_FS_IRQHandler              (void)__attribute__((weak,alias("IRQ_Handler")));

uint32_t vectors[] __attribute__ ((section(".isr_vector"))) ={
    STACK_START,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
    0,
    0,
    0,
    0,
    (uint32_t)&SVCALL_Handler,
    (uint32_t)&DebugMonitor_Handler,
    0,
    (uint32_t)&PendSV_Handler,
    (uint32_t)&SysTick_Handler,
    (uint32_t)&WWDG_IRQHandler,
    (uint32_t)&PVD_IRQHandler,
    (uint32_t)&TAMPER_IRQHandler,
    (uint32_t)&RTC_IRQHandler,
    (uint32_t)&FLASH_IRQHandler,
    (uint32_t)&RCC_IRQHandler,
    (uint32_t)&EXTI0_IRQHandler,
    (uint32_t)&EXTI1_IRQHandler,
    (uint32_t)&EXTI2_IRQHandler,
    (uint32_t)&EXTI3_IRQHandler,
    (uint32_t)&EXTI4_IRQHandler,
    (uint32_t)&DMA1_Channel1_IRQHandler,
    (uint32_t)&DMA1_Channel2_IRQHandler,
    (uint32_t)&DMA1_Channel3_IRQHandler,
    (uint32_t)&DMA1_Channel4_IRQHandler,
    (uint32_t)&DMA1_Channel5_IRQHandler,
    (uint32_t)&DMA1_Channel6_IRQHandler,
    (uint32_t)&DMA1_Channel7_IRQHandler,
    (uint32_t)&ADC1_ADC2_IRQHandler,
    (uint32_t)&CAN1_TX_IRQHandler,
    (uint32_t)&CAN1_RX0_IRQHandler,
    (uint32_t)&CAN1_RX1_IRQHandler,
    (uint32_t)&CAN1_SCE_IRQHandler,
    (uint32_t)&EXTI9_5_IRQHandler,
    (uint32_t)&TIM1_BRK_IRQHandler,
    (uint32_t)&TIM1_UP_IRQHandler,
    (uint32_t)&TIM1_TRG_COM_IRQHandler,
    (uint32_t)&TIM1_CC_IRQHandler,
    (uint32_t)&TIM2_IRQHandler,
    (uint32_t)&TIM3_IRQHandler,
    (uint32_t)&TIM4_IRQHandler,
    (uint32_t)&I2C1_Event_IRQHandler,
    (uint32_t)&I2C1_Error_IRQHandler,
    (uint32_t)&I2C2_Event_IRQHandler,
    (uint32_t)&I2C2_Error_IRQHandler,
    (uint32_t)&SPI1_IRQHandler,
    (uint32_t)&SPI2_IRQHandler,
    (uint32_t)&USART1_IRQHandler,
    (uint32_t)&USART2_IRQHandler,
    (uint32_t)&USART3_IRQHandler,
    (uint32_t)&EXTI15_10_IRQHandler,
    (uint32_t)&RTCAlarm_IRQHandler,
    (uint32_t)&USBWakeUp_IRQHandler,
    0,
    0,
    0,
    (uint32_t)&TIM5_IRQHandler,
    (uint32_t)&SPI3_IRQHandler,
    (uint32_t)&UART4_IRQHandler,
    (uint32_t)&UART5_IRQHandler,
    (uint32_t)&TIM6_IRQHandler,
    (uint32_t)&TIM7_IRQHandler,
    (uint32_t)&DMA2_Channel1_IRQHandler,
    (uint32_t)&DMA2_Channel2_IRQHandler,
    (uint32_t)&DMA2_Channel3_IRQHandler,
    (uint32_t)&DMA2_Channel4_IRQHandler,
    (uint32_t)&DMA2_Channel5_IRQHandler,
    (uint32_t)&Ethernet_IRQHandler,
    (uint32_t)&Ethernet_WAKEUP_IRQHandler,
    (uint32_t)&CAN2_TX_IRQHandler,
    (uint32_t)&CAN2_RX0_IRQHandler,
    (uint32_t)&CAN2_RX1_IRQHandler,
    (uint32_t)&CAN2_SCE_IRQHandler,
    (uint32_t)&OTG_FS_IRQHandler,
};


void Reset_Handler()
{
    //copy .data from Flash to SRAM
    uint32_t size = (uint32_t)&_edata - (uint32_t)&_sdata;
    uint8_t * pointer_to_SRAM = (uint8_t*)&_sdata;
    uint8_t * pointer_from_Flash = (uint8_t*)&_data_from_flash;
    for (uint32_t i = 0; i < size; i++)
    {
        *pointer_to_SRAM++=*pointer_from_Flash++;
    }
    //init .bss=0 in SRAM
    size = (uint32_t)&_ebss - (uint32_t)&_sbss;
    pointer_to_SRAM = (uint8_t*)&_sbss;
    for (uint32_t i = 0; i < size; i++)
    {
        *pointer_to_SRAM++ = 0;
    }

    // call from std lib
    __libc_init_array();

    /*Call System_Init to initialize RCC*/
    System_Init();
    //call main();
    main();
    
}
void DeFault_Handler()
{
    while (1);
}

void IRQ_Handler()
{
    while (1);
    
}