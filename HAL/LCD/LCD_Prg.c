#include "StdTypes.h"
#include "DIO_Int.h"
#include "LCD_Int.h"
#include "LCD_Private.h"
#include "LCD_Cfg.h"


static void WriteIns(u8 ins);
static void WriteData(u8 data);

#if  LCD_MODE==_8_BIT
static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,ins);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

static void WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(FUNCTION_SET);
	WriteIns(LCD_Display);//0x0e,0x0f
	WriteIns(LCD_Clear_Init);//clear screen
	_delay_ms(1);
	WriteIns(LCD_ENTRY);
}
#elif LCD_MODE==_4_BIT

static void WriteIns(u8 ins)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,GET_BIT(ins,7));
	DIO_WritePin(D6,GET_BIT(ins,6));
	DIO_WritePin(D5,GET_BIT(ins,5));
	DIO_WritePin(D4,GET_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,GET_BIT(ins,3));
	DIO_WritePin(D6,GET_BIT(ins,2));
	DIO_WritePin(D5,GET_BIT(ins,1));
	DIO_WritePin(D4,GET_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void WriteData(u8 ins)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,GET_BIT(ins,7));
	DIO_WritePin(D6,GET_BIT(ins,6));
	DIO_WritePin(D5,GET_BIT(ins,5));
	DIO_WritePin(D4,GET_BIT(ins,4));
	
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,GET_BIT(ins,3));
	DIO_WritePin(D6,GET_BIT(ins,2));
	DIO_WritePin(D5,GET_BIT(ins,1));
	DIO_WritePin(D4,GET_BIT(ins,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}

void LCD_Init(void)
{
	_delay_ms(50);
	WriteIns(0x02);
	WriteIns(0x28);
	WriteIns(0x0c);//0x0e,0x0f
	WriteIns(0x01);//clear screen
	_delay_ms(1);
	WriteIns(0x06);
}

#endif
void LCD_WriteChar(c8 ch)
{
	WriteData(ch);
}
void LCD_Clear(void)
{
	WriteIns(LCD_Clear_Init);
	_delay_ms(1);
}
void LCD_WriteString(const c8 *str)
{
	u8 i=0;
	for(i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
}
void LCD_WriteNumber(s32 num)
{
	c8 str[10]={0};
	s8 i=0;
	if(num==0)
	{
		LCD_WriteChar('0');
	}
	else if(num<0)
	{
		LCD_WriteChar('-');
		num=-num;
	}
	else{;}
	while(num)
	{
		str[i++]=(num%10)+'0';
		num/=(10);
	}
	for(i=i-1;i>=0;i--)
	{
		LCD_WriteChar(str[i]);
	}
}
void LCD_WriteBinary(u8 num)
{
	s8 i;
	for (i=7;i>=0;i--)
	{
		LCD_WriteChar(GET_BIT(num,i)+'0');
	}
}
void LCD_WriteHex(u8 num)
{
	u8 LN=(num)&(0x0f);
	u8 HN=num>>4;
	if(HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN+'A'-10);
	}
	if(LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar(LN+'A'-10);
	}
}
void LCD_SetCursor(u8 line ,u8 cell)
{
	if (line==0)
	{
		WriteIns(cell+0x80);
	}
	else
	{
		WriteIns(cell+0x40+0x80);
	}
}
void LCD_ClearCursor(u8 line,u8 cell,u8 NofCells)
{
	LCD_SetCursor(line,cell);
	for (u8 i=0;i<NofCells;i++)
	{
		LCD_WriteChar(' ');
	}
}
void LCD_WriteStringCursor(u8 line, u8 cell, const c8 *str)
{
	LCD_SetCursor(line,cell);
	LCD_WriteString(str);
}
void LCD_CustomChar(const u8 *pattern, u8 address)
{
	WriteIns(0x40+(address*8));
	for(u8 i=0;i<8;i++)
	{
		// WriteIns(0x40+i+(address*8)); no need because writedata inc auto
		WriteData(pattern[i]);
	}
	WriteIns(0x80); // address to write in DDRAM
}


