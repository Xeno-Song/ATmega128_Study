#include "LCD_Control.h"
#include "ButtonMatrix.h"
#include "Calculator.h"
#include "Clock.h"
#include <avr/interrupt.h>

char Mode = 0;

void main(void)
{
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	DDRE = 0x00;

	TCCR0 = 0b00000111;
	TCNT0 = 130;
	TIMSK = 0x01;

	SREG = 0x80;

	InitLCD();
	
	SetWritePos(0x40);

	while(1)
	{
		if(InputProcess() == 1)
		{
			if(GetCurrKey() == 0x8000)
			{
				Mode ^= 1;
				ResetData();
			}

			if(Mode == 1)
				ButtonProcess_Calc(GetCurrKey());

			else
				ButtonProcess_Clock(GetCurrKey());
		}

		TimeProcess(Mode);
	}
}

ISR(TIMER0_OVF_vect)
{
	TimeCounter+= 16;
	TCNT0 = 256-125;
}
