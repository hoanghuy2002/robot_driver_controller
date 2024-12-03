#ifndef _SERIAL_DRIVER_H_
#define _SERIAL_DRIVER_H

void Serial_Initialization(void (*Even_Handler)(void));
void Serial_Write(char *String);
char *Serial_Read(void);
#endif
