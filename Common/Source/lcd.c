#include "lcd.h"
#include "i2c_driver.h"
#include "rcc_driver.h"
#include "delay.h"
#include "stm32f103.h"


#define LCD_I2C                     I2C2
#define LCD_Address                 0x27

#define RS 0
#define RW 1
#define E 2


static void LCD_I2C_Setup()
{
	I2C_ConfigStruct I2C_Custom;
	I2C_Custom.I2C = LCD_I2C;
	I2C_Custom.I2C_ACK = I2C_ACK_Enable;
	I2C_Custom.I2C_ClockStretch = I2C_ClockStretch_Enable;
	I2C_Custom.I2C_GeneralCall = I2C_GeneralCall_Disable;
	I2C_Custom.I2C_NumberBitAddress = I2C_7BitAddress;
	I2C_Custom.I2C_OwnAddress = 0x30;
	I2C_Custom.I2C_SpeedMode = I2C_Standar_SpeedMode;
	I2C_Custom.I2C_APBClockInput = GetAPB1_Clock();
	I2C_Custom.I2C_SCLFrequency = (uint32_t)100000;
	I2C_Init(&I2C_Custom);
}

static void LCD_Command(I2C_RegStruct * I2C,unsigned char Command)
{
	unsigned char Data;
	Data =(unsigned char) (Command & 0xF0)|0x08;
	Data |= (1<<E);
	I2C_MasterTransmit(I2C,I2C_7BitAddress,LCD_Address,&Data,1);
	Data &= ~(1<<E);
	I2C_MasterTransmit(I2C,I2C_7BitAddress,LCD_Address,&Data,1);
	Delay_us(150);
	
	Data =(unsigned char) ((Command<<4)|0x08);
	Data |= (1<<E);     //// E=1
	I2C_MasterTransmit(I2C,I2C_7BitAddress,LCD_Address,&Data,1);
	Data &= ~(1<<E);
	I2C_MasterTransmit(I2C,I2C_7BitAddress,LCD_Address,&Data,1);
    Delay_us(150);
}

static void LCD_Power_On()
{
    unsigned char Data;
    Delay_ms(20);
	LCD_Command(LCD_I2C,0x30);
    Delay_ms(5);
	LCD_Command(LCD_I2C,0x30);
	Delay_us(200);
	LCD_Command(LCD_I2C,0X32);
    Delay_us(200);
}

void LCD_Setup()
{
    Delay_Init(GetAHB_Clock());
    LCD_I2C_Setup();
    LCD_Power_On();
	Delay_us(150);
	LCD_Command(LCD_I2C,0X28);
	Delay_us(150);
	LCD_Clear(LCD_I2C);
	LCD_Command(LCD_I2C,0X0F);
	Delay_us(150);
	LCD_Command(LCD_I2C,0X10);
}

void LCD_Begin(unsigned char position)
{
	LCD_Command(LCD_I2C,position);
	Delay_us(150);
}

void LCD_Clear()
{
	LCD_Command(LCD_I2C,0x01);
	Delay_ms(2);
}

static void LCD_Send_Data(unsigned char I2C_Data)
{
	unsigned char Data;
	Data = (I2C_Data & 0xF0)|0x08;
	Data |= (1<<E)|(1<<RS);
	I2C_MasterTransmit(LCD_I2C,I2C_7BitAddress,LCD_Address,&Data,1);
	Data &= ~(1<<E);
	I2C_MasterTransmit(LCD_I2C,I2C_7BitAddress,LCD_Address,&Data,1);
	Delay_us(100);
	
	Data =(unsigned char) ((I2C_Data<<4))|0x08;
	Data |= (1<<E)|(1<<RS);
	I2C_MasterTransmit(LCD_I2C,I2C_7BitAddress,LCD_Address,&Data,1);
	Data &= ~(1<<E);
	I2C_MasterTransmit(LCD_I2C,I2C_7BitAddress,LCD_Address,&Data,1);
    Delay_us(150);
}

void LCD_Print(unsigned char *String,uint8_t Position)
 {
    uint8_t Word_Count=0;
    LCD_Begin(Position);
    while(*(String+Word_Count))
    {
        LCD_Send_Data(*(String+Word_Count));
        Word_Count+=1;
    }
 }

