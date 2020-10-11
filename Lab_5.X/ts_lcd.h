#ifndef TS_LCD_H
#define TS_LCD_H

extern void ts_lcd_init();

extern uint8_t ts_lcd_get_ts(uint16_t *x, uint16_t *y);

extern void lcd_unit_test();

extern uint8_t screenIsPressed();

#endif
