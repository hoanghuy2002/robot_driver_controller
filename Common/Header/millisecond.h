#ifndef _MilliSecond_H
#define _MilliSecond_H

#include <stdint.h>
#include "timer_driver.h"

void MilliSecond_Setup(void);
void MilliSecond_Start(void);
uint16_t MilliSecond_Stop(void);

#endif