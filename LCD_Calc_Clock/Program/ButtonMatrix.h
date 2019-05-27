#include <avr/io.h>
#include <util/delay.h>

#define BTNMTX_OUT PORTD
#define BTNMTX_IN PINE

//char PrevKey = 0x00;
int PrevKey = 0;
int CurrKey = 0;

void SetOutputLine(unsigned char LineNum)
{
	BTNMTX_OUT = 0x01 << LineNum;
	_delay_us(10);
}

void Input()
{
	char tmp = 0x00;
	CurrKey = 0;

	for(tmp = 0;tmp < 4;tmp++)
	{
		SetOutputLine(tmp);
		CurrKey += BTNMTX_IN & 0x0F;
		
		if(tmp == 3) break;
		
		CurrKey <<= 4;
	}
}
	


char InputProcess()
{
	Input();
	
	if(PrevKey != CurrKey)
	{
		PrevKey = CurrKey;

		if(CurrKey == 0x0001)
			return 1;
			
		if(CurrKey == 0x0010)
			return 2;
		
		if(CurrKey == 0x0100)
			return 3;
			
		if(CurrKey == 0x1000)
			return 4;
	}

	return 0;
}

int GetCurrKey()
{
	return CurrKey;
}
