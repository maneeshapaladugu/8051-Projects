#include<reg51.h>
#include"types.h"
#define lcd P0

extern delay_ms(unsigned int);

sbit RS=P2^1;
sbit RW=P2^2;
sbit EN=P2^3;

void LCD_write(u8 dat)
{
	RW=0;
	lcd=dat;
	EN=1;
	delay_ms(2);
	EN=0;
}
void LCD_data(u8 ch)
{
	RS=1;
	LCD_write(ch);
}
void LCD_cmd(u8 cmd)
{
	RS=0;
	LCD_write(cmd);
}
void LCD_str(u8 *p)
{
	while(*p)
		LCD_data(*p++);
}
void LCD_int(u32 n)
{
	u8 a[11],i=0;
	if(n==0)
		LCD_data('0');
	else
	{
		while(n)
		{
			a[i++]=n%10;
			n/=10;
		}
		for(;i>0;i--)
		{
			LCD_data(a[i-1]+'0');
		}
	}
}
void LCD_init(void)
{
	LCD_cmd(0x38);
	LCD_cmd(0x06);
	LCD_cmd(0x0c);
}