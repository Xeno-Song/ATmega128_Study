#include <avr/io.h>
#include <util/delay.h>

#ifndef __LCD_CONTROL_H__
#define __LCD_CONTROL_H__

#define LCD_STRU		PORTC
#define LCD_DATA		PORTA

#define ENABLE_BIT		0x04
#define RS_BIT			0x01
#define RW_BIT			0x02


#define DISPLAY_CLEAR	0x01
#define CURSOR_HOME		0x02

//Command Write
void LCD_Command(unsigned char data)
{
	LCD_STRU = 0x00;
	LCD_DATA = data;
	_delay_us(1);

	LCD_STRU |= ENABLE_BIT;
	_delay_us(10);

	LCD_STRU = 0;
	_delay_ms(1);
}

//Data Write
void LCD_Data(unsigned char data)
{
	LCD_STRU = RS_BIT;

	LCD_DATA = data;
	_delay_us(1);

	LCD_STRU |= ENABLE_BIT;
	_delay_us(10);

	LCD_STRU = 0;
	_delay_us(50);
}

//Init LCD
void InitLCD()
{
	LCD_DATA = 0x00;
	LCD_STRU = 0x00;
	_delay_ms(100);

	//Function set
	LCD_Command(0x3C);
	_delay_ms(10);

	//Function set
	LCD_Command(0x3C);
	_delay_us(100);

	LCD_Command(0x3C);
	_delay_us(100);

	LCD_Command(0x3C);	//Function Set
	LCD_Command(0x0C);	//Display Control
	LCD_Command(DISPLAY_CLEAR); //Display Clear
	LCD_Command(0x06);		//Set Entrymode
}

void SetWritePos(char address)
{
	LCD_Command(address | 0x80);
}

void LCD_WriteString(char* str)
{
	while(*str != 0)
	{
		LCD_Data(*str);
		str++;
	}
}

void LCD_NumPrintLoop(long Num)
{
	if(Num >= 10)
		LCD_NumPrintLoop(Num / 10);

	LCD_Data(Num % 10 + '0');
}

void LCD_WriteNum(long Num)
{
	if(Num < 0)
	{
		LCD_Data('-');
		Num *= -1;
	}

	LCD_NumPrintLoop(Num);
}

#endif
