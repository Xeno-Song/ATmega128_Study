#include "LCD_Control.h"

char Hours, Minutes, Seconds;
char TimeCounter = 0;

void WriteTime()
{
	char tmp;
	SetWritePos(0x00);

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

void ButtonProcess_Clock(int Key)
{
	if(Key == 0x0001)
	{
		Minutes++;
		
		if(Minutes == 60) Minutes = 0;
	}
	else if(Key == 0x0010)
	{
		if(Minutes == 0) Minutes = 60;
		Minutes--;
	}
	
	if(Key == 0x0100)
	{
		Hours++;
		
		if(Hours == 24) Hours = 0;
	}
	else if(Key == 0x1000)
	{
		if(Hours == 0) Hours = 24;
		Hours--;
	}
	
	if(Key == 0x2000)
		Seconds = 0;

	if(Key == 0x4000)
		Hours = Minutes = Seconds = 0;
}

void TimeProcess(char OutputMode)
{
	if(OutputMode == 0)
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
}


