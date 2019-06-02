#include "LCD_Control.h"

long Result, CurrNum;
char PrevSign;
char Equaled;

/*
1. +
2. -
3. *
4. /
*/

void ResetData()
{
	CurrNum = 0;
	Result = 0;
	PrevSign = 0;
	LCD_Command(0x01);
}
	

void AppendNum(char n)
{
	if(Equaled == 2)
	{
		CurrNum = 0;
		Equaled = 0;
		LCD_Command(0x01);
	}

	SetWritePos(0x40);
	
	if(CurrNum >= 100000000)
	{
		LCD_WriteString("OVERFLOW    ");
		_delay_ms(50);

		ResetData();
		return;
	}

	CurrNum = CurrNum * 10 + n;
	LCD_WriteNum(CurrNum);
}

void CalcNum(char Sign)
{	
	GetResult(PrevSign, Sign);
	PrevSign = Sign;

	switch(Sign)
	{
	case 1:
		LCD_WriteString(" + ");
		break;

	case 2:
		LCD_WriteString(" - ");
		break;
	
	case 3:
		LCD_WriteString(" * ");
		break;

	case 4:
		LCD_WriteString(" / ");
		break;
	}
}

void GetResult(char PrevSign, char Sign)
{
	long m_Result = 0;

	switch(PrevSign)
	{
	case 1:
		m_Result = Result + CurrNum;
		break;

	case 2:
		m_Result = Result - CurrNum;
		break;

	case 3:
		m_Result = Result * CurrNum;
		break;

	case 4:
		m_Result = Result / CurrNum;
		break;

	case 0:
		if(Sign != 0)
			m_Result = CurrNum;

		break;
	}

	CurrNum = 0;
	Result = 0;
	
	LCD_Command(0x01);

	if(Sign == 0 && PrevSign != 0)
	{
		Equaled++;
		CurrNum = m_Result;
		LCD_WriteNum(CurrNum);
	}
	
	else if(Sign != 0)
	{
		Result = m_Result;
		LCD_WriteNum(Result);
	}
}

int ButtonProcess_Calc(int Key)
{
	switch(Key)
	{
	case 0x0800:
		AppendNum(0);
		break;

	case 0x4000:
		AppendNum(1);
		break;

	case 0x0400:
		AppendNum(2);
		break;

	case 0x0040:
		AppendNum(3);
		break;

	case 0x2000:
		AppendNum(4);
		break;

	case 0x0200:
		AppendNum(5);
		break;

	case 0x0020:
		AppendNum(6);
		break;

	case 0x1000:
		AppendNum(7);
		break;

	case 0x0100:
		AppendNum(8);
		break;

	case 0x0010:
		AppendNum(9);
		break;

	case 0x0080:
		CalcNum(0);
		break;

	case 0x0001:
		CalcNum(1);
		break;

	case 0x0002:
		CalcNum(2);
		break;

	case 0x0004:
		CalcNum(3);
		break;

	case 0x0008:
		CalcNum(4);
		break;
	}
}
