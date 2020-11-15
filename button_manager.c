#include <xc.h>
#include <inttypes.h>

#include "ts_lcd.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"

#define NUMBER_OF_BOXES 20
#define Y_DIST_BETWEEN_BUTTONS 46
#define X_DIST_BETWEEN_BUTTONS 79

// Returns -1 if the screen is not pressed or the press is out of bounds of the buttons.
// Returns 0-9 if any of the number buttons are pressed.
// returns +:10,  -:11,  x:12,  /:13,  C:14,  =:15
int8_t button_detect(){

  uint8_t result[16] = {7, 8, 9, 10, 4, 5, 6, 11, 1, 2, 3, 12, 0, 14, 15, 13};

  if(screenIsPressed()){
      uint16_t displayX, displayY;

      ts_lcd_get_ts(&displayX, &displayY);

      if(displayY < 54){
        return -1;
      }

      displayY -= 54;

      int y = 0;
      for(; y < 4; y++){
        int x = 0;
        for(; x < 4; x++){
          if(displayX >= (x * X_DIST_BETWEEN_BUTTONS) && // If x input is greater than the left edge of the current button.
             displayX <= (x * X_DIST_BETWEEN_BUTTONS) + 79 && // If x input is less than the right edge of the current button.
             displayY >= (y * Y_DIST_BETWEEN_BUTTONS) &&
             displayY <= (y * Y_DIST_BETWEEN_BUTTONS) + 46)

             return result[(x + y * 4)];
        }
      }
  }


  return -1;
}

void draw_buttons(){

  uint16_t xTextOffset = 33, yTextOffset = 16;

  char buttonText[NUMBER_OF_BOXES] = {'7', '8', '9', '+',
                                      '4', '5', '6', '-',
                                      '1', '2', '3', 'x',
                                      '0', 'C', '=', '/',};

  uint16_t button_color[NUMBER_OF_BOXES] = {ILI9341_WHITE, ILI9341_WHITE, ILI9341_WHITE, ILI9341_YELLOW,
                              ILI9341_WHITE, ILI9341_WHITE, ILI9341_WHITE, ILI9341_YELLOW,
                              ILI9341_WHITE, ILI9341_WHITE, ILI9341_WHITE, ILI9341_YELLOW,
                              ILI9341_WHITE, ILI9341_RED, ILI9341_BLUE, ILI9341_YELLOW};

  tft_fillRect(4, 4, 312, 48, ILI9341_WHITE);
  tft_setTextSize(2);

  int y = 0;
  for(; y < 4; y++){
    int x = 0;
    for(; x < 4; x++){
      tft_fillRect(4   + (x * X_DIST_BETWEEN_BUTTONS), // X-coordinate of the top left corner shifted depending on which button this is.
                   56  + (y * Y_DIST_BETWEEN_BUTTONS), // Y-coordinate.
                   75, // Width of the box.
                   42, // Height of the box.
                   button_color[x + y * 4]);

      tft_setTextColor(ILI9341_BLACK);
      tft_setCursor(4   + (x * X_DIST_BETWEEN_BUTTONS) + xTextOffset, 56  + (y * Y_DIST_BETWEEN_BUTTONS) + yTextOffset);
      tft_write(buttonText[x + y * 4]);
    }
  }


}
