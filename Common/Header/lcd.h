#ifndef _LCD_H_
#define _LCD_H_
#include <stdint.h>

void LCD_Setup();
void LCD_Begin(unsigned char position);
void LCD_Clear();
void LCD_Print(unsigned char *String,uint8_t Position);

#endif