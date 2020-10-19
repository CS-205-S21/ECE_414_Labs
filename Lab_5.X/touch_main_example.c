/*
 * File:   touch_main.c
 * Author: watkinma
 *
 * Description: Prints out the detected position (x, y) of a press on the
 * touchscreen as well as the pressure (z).
 *
 * IMPORTANT: For this example to work, you need to make the following
 * connections from the touchpad to the PIC32:
 *  Y+ => AN1 (Pin 3)
 *  Y- => RA3 (Pin 10)
 *  X+ => RA4 (Pin 12)
 *  X- => AN0 (Pin 2)
 *
 */

#include <xc.h>
#include <plib.h>
#include "config.h"
//#include "adc_intf.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"
#include "calculator.h"

#define XM AN0
#define YP AN1

int main(int argc, char** argv) {
    static char buffer[30];
    uint8_t action = 0;

    ts_lcd_init();

    draw_buttons();

    int8_t input = button_detect(), x = 16;
    
    int64_t calcResult;

    while(1){
      //lcd_unit_test();

      input = button_detect();

      if(screenIsPressed() && action == 0){ // The screen was just released.
        action = 1;

        if(input >= 0) // If there was a valid input.
            x = input;
      }
      calcResult = tickFct_CALCULATOR(x);
      x = 16;

      if(!screenIsPressed())
        action = 0;

      /*
      if(pressed && !screenIsPressed()) // The screen was just released.
        if(input >= 0) // If there was a valid input.
            calcResult = tickFct_CALCULATOR(input);
            */

      tft_fillRect(4, 4, 312, 48, ILI9341_WHITE);
      tft_setTextSize(2);
      tft_setCursor(37, 20);
      tft_setTextColor(ILI9341_BLACK);
      if(calcResult >= -1000)
        sprintf(buffer, "%d", calcResult);
      else if(calcResult == -1001)
        sprintf(buffer,"ERROR");
      else if(calcResult == -1002)
        sprintf(buffer,"DIV0");

      tft_writeString(buffer);

      delay_ms(20);
    }

    return (EXIT_SUCCESS);
}
