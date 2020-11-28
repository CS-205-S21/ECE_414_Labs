#include <xc.h>
#include <inttypes.h>
#include "display_manager.h"
#include "tft_master.h"
#include "tft_gfx.h"

#define BUFFER_SIZE 30

uint16_t ts;

uint16_t UARTHead = 0, xPosition = 10;
//uint16_t speeds[300] = {0};
char UARTCommand[BUFFER_SIZE];
char buffer2[BUFFER_SIZE];

void setTargetSpeed(uint16_t targetSpeed){
    ts = targetSpeed;
    tft_fillRect(10, 10, 300, 66, ILI9341_WHITE);

}

void setNextUARTChar(char c){
  UARTCommand[UARTHead++] = c;

  if(c == '\r'){
    UARTHead = 0;
    tft_setTextColor(ILI9341_WHITE);
    tft_setCursor(16, 38);
    tft_writeString(buffer2);
    uint16_t i;
    for( i=0; i < BUFFER_SIZE; i++)
      buffer2[i] = ' ';
  }
}

void updateDisplayText(uint16_t currentSpeed){
  static char buffer[BUFFER_SIZE];
  static uint16_t cs;

  tft_setTextSize(2);
  tft_setTextColor(ILI9341_WHITE);

  tft_setCursor(16, 16);
  sprintf(buffer, "TS: %d,   CS: %d", ts, cs);
  tft_writeString(buffer);

  tft_setTextColor(ILI9341_BLACK);

  tft_setCursor(16, 16);
  sprintf(buffer, "TS: %d,   CS: %d", ts, currentSpeed);
  tft_writeString(buffer);

  cs = currentSpeed;

  tft_setTextColor(ILI9341_WHITE);
  tft_setCursor(16, 38);
  tft_writeString(buffer2);

  int16_t i;
  for(i = 0; i < UARTHead; i++)
    buffer2[i] = UARTCommand[i];

  tft_setTextColor(ILI9341_BLACK);
  tft_setCursor(16, 38);
  tft_writeString(buffer2);

}

void updateDisplayGraphics(uint16_t currentSpeed){

  if(currentSpeed < 3000){
    // Draw graphic speed display. -------------------------------------------------------------------------
    tft_drawPixel(xPosition, 229 - (ts / 20), ILI9341_GREEN);
    tft_drawPixel(xPosition++, 229 - (currentSpeed / 20), ILI9341_RED);

    if(xPosition >= 310){
        tft_fillRect(10, 80, 300, 150, ILI9341_BLACK);
        xPosition = 10;
    }
  }
}
