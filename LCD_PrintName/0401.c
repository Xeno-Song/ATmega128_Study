#include "LCD_Control.h"
#include <avr/interrupt.h>

char Hours, Minutes, Seconds;
char TimeCounter = 0;

void WriteTime()
{
	char tmp;
	Set_Data_Memory_Address(0x00);

	tmp = Hours;
	LCD_Data('0' + (char)(tmp / 10));
	LCD_Data('0' + (char)(tmp % 10));

	LCD_Data(':');

	tmp = Minutes;
	LCD_Data('0' + (char)(tmp / 10));
	LCD_Data('0' + (char)(tmp % 10));

	LCD_Data(':');

	tmp = Seconds;
	LCD_Data('0' + (char)(tmp / 10));
	LCD_Data('0' + (char)(tmp % 10));
}

int main()
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	
	InitLCD();

	LCD_WriteString("Lee Seong Jun");

	Set_Data_Memory_Address(0x40);
	LCD_WriteString("Song Jae Hyuck");
		

	while(1);
}


