#ifndef _DELAY_H_
#define _DELAY_H_

#include <stdint.h>

void Delay_Init(uint32_t System_CLK);
void Delay_us(uint32_t Time_Delay);
void Delay_ms(uint32_t Time_Delay);
#endif