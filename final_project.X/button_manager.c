#include <xc.h>
#include <inttypes.h>

#include "ts_lcd.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"

#define NUMBER_OF_BOXES 20
#define Y_DIST_BETWEEN_BUTTONS 40
#define X_DIST_BETWEEN_BUTTONS 38

// Returns -1 if the screen is not pressed or the press is out of bounds of the buttons.
int8_t game_button_detect(){

  if(screenIsPressed()){
      uint16_t displayX, displayY;

      ts_lcd_get_ts(&displayX, &displayY);

      // Loop through each of the board spaces and return the related number if any of those spaces are pressed.
      uint16_t y = 0;
      for(; y < 6; y++){
        uint16_t x = 0;
        for(; x < 6; x++){
          if(displayX >= (x * X_DIST_BETWEEN_BUTTONS) + 15 && // If x input is greater than the left edge of the current button.
             displayX <= ((x + 1) * X_DIST_BETWEEN_BUTTONS) + 15 && // If x input is less than the right edge of the current button.
             displayY >= (y * Y_DIST_BETWEEN_BUTTONS) &&
             displayY <= ((y + 1) * Y_DIST_BETWEEN_BUTTONS))

             return (x + y * 6);
        }
      }

      // If the user has pressed the "Clear" button return 36.
      if(displayX >= 246 &&
         displayX <= 318 &&
         displayY >= 154 &&
         displayY <= 194 )
         return 36;

     // If the user has pressed the "Menu" button return 37.
     if(displayX >= 246 &&
        displayX <= 318 &&
        displayY >= 200 &&
        displayY <= 240 )
        return 37;

  }

  return -1;
}

void draw_buttons(unsigned short colorBoard,
                  unsigned short colorBackground,
                  unsigned short colorLine,
                  unsigned short colorText,
                  unsigned short colorButtons){

//Background
  tft_fillScreen(colorBackground);

// Board
  tft_fillRect(6, 6, 228, 228, colorBoard);

// Thick lines
  tft_fillRect(120, 6,   2, 228, colorLine); // Vertical
  tft_fillRect(6,   82,  228, 2, colorLine); // Horizontal 1
  tft_fillRect(6,   158, 228, 2, colorLine); // Horizontal 2

// Thin lines
  tft_drawFastVLine(44, 6,  228, colorLine);
  tft_drawFastVLine(82, 6,  228, colorLine);
  tft_drawFastVLine(158, 6, 228, colorLine);
  tft_drawFastVLine(196, 6, 228, colorLine);

  tft_drawFastHLine(6, 44,  228, colorLine);
  tft_drawFastHLine(6, 120, 228, colorLine);
  tft_drawFastHLine(6, 196, 228, colorLine);

// Buttons
  tft_fillRect(240, 28,  72, 35, ILI9341_WHITE);
  tft_fillRect(240, 158, 72, 35, colorButtons);
  tft_fillRect(240, 199, 72, 35, colorButtons);

// Button text
  tft_setTextSize(2);
  tft_setTextColor(colorText);
  tft_setCursor(246,6);
  tft_writeString("Timer");
  tft_setCursor(243,69);
  tft_writeString("Number");
  tft_setCursor(246,167);
  tft_writeString("Clear");
  tft_setCursor(252,210);
  tft_writeString("Menu");

}
