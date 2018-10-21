#include<reg51.h>
#include"types.h"

extern void delay_ms(u16);

sbit SCL=P2^4;
sbit SDA=P2^5;

void i2cStart(void)
{
	SCL=1;
	SDA=1;
	SDA=0;
}
void i2cStop(void)
{
	SCL=0;
	SDA=0;
	SCL=1;
	SDA=1;
}
void i2cWrite(u8 dat)
{
	u8 i;
	for(i=0;i<8;i++)
	{
		SCL=0;
		SDA=(dat<<i) & 0x80?1:0;
		SCL=1;
	}
}
u8 i2cRead(void)
{
	u8 dat=0,i;
	for(i=0;i<8;i++)
	{
		SCL=0;
		SCL=1;
		if(SDA)
			dat|=0x80>>i;
	}
	return dat;
}
void i2cAck(void)
{
	SCL=0;
	SDA=1;
	SCL=1;
	while(SDA);
}
void i2cNoAck(void)
{
	SCL=0;
	SDA=1;
	SCL=1;
}
void i2cMasterAck(void)
{
	SCL=0;
	SDA=0;
	SCL=1;
	SCL=0;
	SDA=1;
}
void i2cRestart(void)
{
	SCL=0;
	SDA=1;
	SCL=1;
	SDA=0;
}
void i2cDevWrite(u8 sa,u8 buff,u8 dat)
{
	i2cStart();
	i2cWrite(sa & 0xfe);
	i2cAck();
	i2cWrite(buff);
	i2cAck();
	i2cWrite(dat);
	i2cAck();
	i2cStop();
	delay_ms(10);
}
u8 i2cDevRead(u8 sa,u8 rbuff)
{
	u8 buff;
	i2cStart();
	i2cWrite(sa & 0xfe);
	i2cAck();
	i2cWrite(rbuff);
	i2cAck();
	i2cRestart();
	i2cWrite(sa | 0x01);
	i2cAck();
	buff=i2cRead();
	i2cNoAck();
	i2cStop();
	return buff;
}