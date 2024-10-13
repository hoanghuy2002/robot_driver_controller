#include "delay.h"

uint32_t HCLK = 0;
void Delay_Init(uint32_t System_CLK)
{
    HCLK = System_CLK;
}

void Delay_ms(uint32_t Time_Delay)
{
    uint32_t Loop_Time = 0;
    Loop_Time = (uint32_t)(Time_Delay/(15.0*1000000/HCLK));
		for (uint16_t i = 1000; i > 0; i--)
		{
			for (uint32_t Counter = Loop_Time; Counter>0; Counter--);
		}
}

void Delay_us(uint32_t Time_Delay)
{
    uint32_t Loop_Time = 0;
    Loop_Time = (uint32_t)((Time_Delay-5)/(16.0*1000000/HCLK));
    for (Loop_Time; Loop_Time>0; Loop_Time--);
}