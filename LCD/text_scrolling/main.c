#include"lcd_h.h"
#include"types.h"

extern delay_ms(u16);

void main()
{
	u8 i,cur,start;
	
	LCD_init();
	LCD_cmd(0x0c);//To disable cursor-and-cursor blinking
	start = 0x80;
	while(1)
	{
		LCD_cmd(0x01);
		LCD_cmd(start);
		cur = start;
		for(i=0;i<5;i++)
		{
			LCD_data("Manoj"[i]);
			cur++;
			if(cur == 0x90)
			{
				cur = 0x80;
				LCD_cmd(0x80);
			}
		}
    start++;
		if(start == 0x90)
		{
			start = 0x80;
		}
		delay_ms(100);
	}
}