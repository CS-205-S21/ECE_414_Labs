#include <xc.h>
#include <inttypes.h>

#include "ts_lcd.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"

void ts_lcd_init(){

  SYSTEMConfigPerformance(PBCLK);

  configureADC();

  //initialize screen
  tft_init_hw();
  tft_begin();
  tft_setRotation(3);
  tft_fillScreen(ILI9341_BLACK);

}

uint8_t ts_lcd_get_ts(uint16_t *x, uint16_t *y){

  struct TSPoint p;
  p.x = 0;
  p.y = 0;
  getPoint(&p);

  *x = 320-((float)(p.y-130) / (800.0f)) * (320.0f);
  *y = ((float)(p.x - 180) / (680.0f)) * (240.0f);
}

void lcd_unit_test(){
  static char buffer[30];

  static uint16_t displayX, displayY;

  if(screenIsPressed()){
    tft_drawLine(displayY - 10, displayX,      displayY + 10, displayX,      0x0000); // Erase the old cursor.
    tft_drawLine(displayY,      displayX + 10, displayY,      displayX - 10, 0x0000);

    ts_lcd_get_ts(&displayY, &displayX);

    tft_setCursor(10, 10);
    tft_setTextSize(2);

    //erase old text
    tft_setTextColor(ILI9341_BLACK);
    tft_writeString(buffer);

    tft_setCursor(10, 10);
    tft_setTextColor(ILI9341_WHITE);
    sprintf(buffer,"x: %d, y: %d", displayX, displayY);
    tft_writeString(buffer);

    tft_drawLine(displayY - 10, displayX,      displayY + 10, displayX,      0xffff);
    tft_drawLine(displayY,      displayX + 10, displayY,      displayX - 10, 0xffff);
  }
}


uint8_t screenIsPressed(){
  struct TSPoint p;
  p.x = 0;
  p.y = 0;
  getPoint(&p);
  return (p.z > 0);
}
