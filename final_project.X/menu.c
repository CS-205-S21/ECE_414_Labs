#include <xc.h>
#include <inttypes.h>

#include "ts_lcd.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"
#include "menu.h"

#define NUMBER_OF_BUTTONS 9

void menu_setup(unsigned short colorBackground, unsigned short colorText, unsigned short colorButtons){
    tft_fillScreen(colorBackground);

    tft_setTextSize (5);
    tft_setTextColor(colorText);
    tft_setCursor(100, 26);
    tft_writeString("Menu");
    tft_setTextSize (2);
    tft_setCursor(15, 90);
    tft_writeString("Color Theme");
    tft_setCursor(15, 125);
    tft_writeString("Game Level");

    tft_fillRect(60, 170, 200, 50, colorButtons);
    tft_setTextSize (3);
    tft_setCursor(73, 183);
    tft_writeString("Start Game");

    // Color Theme Blocks
    tft_fillRect(170, 90, 20, 20, ILI9341_WHITE);
    tft_fillRect(196, 90, 20, 20, ILI9341_CYAN);
    tft_fillRect(222, 90, 20, 20, ILI9341_GREENYELLOW);
    tft_fillRect(248, 90, 20, 20, ILI9341_YELLOW);
    tft_fillRect(274, 90, 20, 20, ILI9341_PURPLE);

    // Level Blocks
    tft_fillRect(170, 130, 10, 10, colorButtons); //easy
    tft_fillRect(207, 130, 10, 10, colorButtons); //medium
    tft_fillRect(220, 130, 10, 10, colorButtons); //medium
    tft_fillRect(258, 130, 10, 10, colorButtons); //hard
    tft_fillRect(271, 130, 10, 10, colorButtons); //hard
    tft_fillRect(284, 130, 10, 10, colorButtons); //hard
}

// Returns -1 if the screen is not pressed or the press is out of bounds of the buttons.
int8_t menu_button_detect(){

    if(screenIsPressed()){
        const uint16_t buttonCoordinates[NUMBER_OF_BUTTONS][4] = { {182, 88, 203, 108}, // Format: {x, y, x, y}
                                                                   {209, 88,  229, 108},
                                                                   {235, 88,  255, 108},
                                                                   {261, 88,  281, 108},
                                                                   {287, 88,  307, 108},
                                                                   {178, 125, 198, 145},
                                                                   {214, 125, 245, 145},
                                                                   {264, 125, 310, 145},
                                                                   {60,  170, 260, 220},};

        uint16_t displayX, displayY;
        ts_lcd_get_ts(&displayX, &displayY); // Make displayX and displayY contain the coordinates of the touch input on the screen.
        uint8_t i;

        // Cycle through each button position and if the input is located in one of the button locations, return that button number code.
        for(i = 0; i < NUMBER_OF_BUTTONS; i++)
            if(displayX >= buttonCoordinates[i][0] &&
               displayX <= buttonCoordinates[i][2] &&
               displayY >= buttonCoordinates[i][1] &&
               displayY <= buttonCoordinates[i][3])
               return i;
    }

    return -1;
}
