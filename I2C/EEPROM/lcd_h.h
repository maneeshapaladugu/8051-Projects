#ifndef _lcd_
#define _lcd_
#include"types.h"
extern void LCD_int(u32);
extern void LCD_init(void);
extern void LCD_str(u8*);
extern void LCD_cmd(u8);
extern void LCD_data(u8);
#endif