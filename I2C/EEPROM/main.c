#include"lcd_h.h"
#include"i2c_h.h"
#include"types.h"

extern delay_ms(u16);

void main()
{
	u8 i;
	LCD_init();
	LCD_cmd(0x01);
	LCD_str("EEPROM TEST...");
	delay_ms(1000);
	for(i = 0;i < 5; i++)
	{
		i2cDevWrite(0xa0,i,'A'+i);
	}
	LCD_cmd(0x01);
	for(i = 0;i < 5; i++)
	{
		LCD_data(i2cDevRead(0xa0,i));
	}
	delay_ms(5000);
	while(1);
}