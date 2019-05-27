#include <avr/io.h>
#include <util/delay.h>

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

void Set_Data_Memory_Address(char address)
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

void LCD_WriteNum(unsigned char Num)
{
	if(Num >= 10)
	{
		if(Num >= 100)
		{
			LCD_Data((Num / 100) + '0');
		}

		LCD_Data((Num /10) % 10 + '0');
	}

	LCD_Data(Num % 10 + '0');

	LCD_WriteString("   ");
}
