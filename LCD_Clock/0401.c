#include "LCD_Control.h"
#include "ButtonMatrix.h"
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
	char cnt = 0;
	char tmp = 0;

	Hours = Minutes = Seconds = 0;

	DDRA = 0xFF;
	DDRC = 0xFF;

	DDRE = 0x00;
	DDRD = 0xFF;

	InitLCD();
	
	TCCR0 = 0b00000111;
	TCNT0 = 130;
	TIMSK = 0x01;

	SREG = 0x80;
	//LCD_WriteString("TESTING");

	WriteTime();
	SetOutputLine(0);

	while(1)
	{
		WriteTime();
		
		if(TimeCounter >= 125)
		{
			TimeCounter -= 125;
			Seconds++;
			if(Seconds == 60)
			{
				Minutes++;
				Seconds = 0;

				if(Minutes == 60)
				{
					Hours++;
					Minutes = 0;

					if(Hours == 24)
						Hours = 0;
				}
			}
		}

		tmp = InputProcess();

		if(tmp == 2)
		{
			Minutes++;

			if(Minutes == 60) Minutes = 0;
		}
		else if(tmp == 1)
		{
			if(Minutes == 0) Minutes = 60;

			Minutes--;
		}
		

		if(tmp == 4)
		{
			Hours++;
			
			if(Hours == 24) Hours = 0;
		}
		else if(tmp == 3)
		{
			if(Hours == 0) Hours = 24;

			Hours--;
		}
	}	
}


ISR(TIMER0_OVF_vect)
{
	TimeCounter+= 16;
	TCNT0 = 256-125;
}



