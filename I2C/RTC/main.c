#include"lcd_h.h"
#include"i2c_h.h"

extern delay_ms(u16);

void main()
{
  u8 hrs = 0x23, mins = 0x59, secs = 0x50;
	
	LCD_init();
	LCD_str("I2C RTC TEST");
	delay_ms(1000);
	LCD_cmd(0x01);
	LCD_str("Config Time...");
	i2cDevWrite(0xd0,0x02,hrs);
	i2cDevWrite(0xd0,0x01,mins);
	i2cDevWrite(0xd0,0x00,secs);
	delay_ms(1000);
	LCD_cmd(0x01);
	LCD_str("Reading Time...");
	while(1)
	{
		LCD_cmd(0xc0);
		hrs = i2cDevRead(0xd0,0x02);
		LCD_data((hrs/16)+48);
		LCD_data((hrs%16)+48);
		LCD_data(':');
		
		mins = i2cDevRead(0xd0,0x01);
		LCD_data((mins/16)+48);
		LCD_data((mins%16)+48);
		LCD_data(':');
		
		secs = i2cDevRead(0xd0,0x00);
		LCD_data((secs/16)+48);
		LCD_data((secs%16)+48);
	}
}