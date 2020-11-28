#include <xc.h>
#include <inttypes.h>
#include "tft_master.h"
#include "tft_gfx.h"
#include "displayClock.h"

uint16_t minutes = 0, seconds = 0;

void increment_timer(unsigned short colorText){
    static char buffer[10];

    tft_setTextSize(2);
    tft_setTextColor(ILI9341_WHITE);
    tft_setCursor(246, 40);
    tft_writeString(buffer);

    if(seconds++ >= 59){
        minutes++;
        seconds = 0;
    }

    sprintf(buffer, "%02d:%02d", minutes, seconds);

    tft_setTextColor(colorText);
    tft_setCursor(246, 40);
    tft_writeString(buffer);
}

void reset_timer(unsigned short colorText){
    char buffer[10];
    sprintf(buffer, "%02d:%02d", minutes, seconds);

    tft_setTextSize(2);
    tft_setTextColor(ILI9341_WHITE);
    tft_setCursor(246, 40);
    tft_writeString(buffer);

    minutes = 0;
    seconds = 0;
}
