#include <avr/io.h>
#include <util/delay.h>

#define BTNMTX_OUT PORTE
#define BTNMTX_IN PINE

void SetOutputLine(unsigned char LineNum)
{
	PORTE = 0x01 << LineNum;
	_delay_ms(1);
}

void GetButtonMatrix(char* Matrix)
{
	for(unsigned char i = 0;i < 4;i++)
	{
		SetOutputLine(i);

		unsigned char tmp = PINE & 0xF0;
		tmp >>= 4;

		for(unsigned char j = 0;j < 4;j++)
		{
			*(Matrix + (4 - j)) = tmp % 2;
			tmp /= 2;
		}

		Matrix += 4;
	}
}

char GetButtonState(unsigned x, unsigned y)
{
	SetOutputLine(y);
	return ((PINE & 0xF0) >> 4) >> x;
}
