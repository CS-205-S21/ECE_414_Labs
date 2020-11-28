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
#include "UART1.h"
#include "timer1p.h"
#include "menu.h"
#include "displayClock.h"

#define XM AN0
#define YP AN1

void startMenu();
void startGame();

uint16_t ta1, ta2, tb1, tb2; // Timervariables

unsigned short colorBoard = ILI9341_WHITE,
                colorBackground = 0x62EC,
                colorLine = ILI9341_BLACK,
                colorText = ILI9341_BLACK,
                colorButtons = 0xB5B6;

uint8_t *startingBoard;
uint8_t board1[36] = { 0, 0, 3, 0, 1, 0,
                       5, 6, 0, 3, 2, 0,
                       0, 5, 4, 2, 0, 3,
                       2, 0, 6, 4, 5, 0,
                       0, 1, 2, 0, 4, 5,
                       0, 4, 0, 1, 0, 0},

       board2[36] = { 0, 0, 0, 1, 0, 6,
                      6, 0, 4, 0, 0, 0,
                      1, 0, 2, 0, 0, 0,
                      0, 0, 0, 5, 0, 1,
                      0, 0, 0, 6, 0, 3,
                      5, 0, 6, 0, 0, 0},

       board3[36] = { 6, 0, 0, 0, 0, 2,
                     0, 4, 0, 0, 3, 0,
                     0, 0, 0, 0, 0, 0,
                     0, 1, 0, 0, 4, 0,
                     3, 0, 0, 0, 0, 6,
                     0, 0, 0, 0, 0, 0};



int main(int argc, char** argv) {

    // LCD screen setup
    ts_lcd_init();

    // UART setup
    uart1_init(9600);

    // Output Pin setup
    PORTSetPinsDigitalOut (IOPORT_B, BIT_4 | BIT_5 | BIT_7 | BIT_8 | BIT_9 | BIT_10 | BIT_13 | BIT_15);
    PORTClearBits(IOPORT_B, BIT_4 | BIT_5 | BIT_7 | BIT_8 | BIT_9 | BIT_10 | BIT_13 | BIT_15);

    // Set the initial board.
    startingBoard = board1;
    set_starting_board(startingBoard);
    tft_fillRect(170, 130, 10, 10, colorText);

    while(1){
      startMenu();
      startGame();
    }

    return (EXIT_SUCCESS);
}

void startMenu(){
  int8_t flag = 0;

  menu_setup(colorBackground, colorText, colorButtons);

  while(flag != 8) { // While the user has not pressed the "Start Game" button.
      ta2 = tb2 = timer1_read();

      flag = menu_button_detect(); // Menu button detect returns -1 if the screen is not pressed, and a set number if one of the buttons is pressed.

      if(flag == 0){ // Set the theme to white.
        colorBoard = ILI9341_WHITE,
        colorBackground = 0x62EC,
        colorLine = ILI9341_BLACK,
        colorText = ILI9341_BLACK,
        colorButtons = 0xB5B6;
        menu_setup(colorBackground, colorText, colorButtons);
      }
      else if(flag == 1){ // Set the theme to blue.
        colorBoard = ILI9341_CYAN,
        colorBackground = ILI9341_DARKCYAN,
        colorLine = 0x09C9,
        colorText = 0x09C9,
        colorButtons = 0xCEFC;
        menu_setup(colorBackground, colorText, colorButtons);
      }
      else if(flag == 2){ // Set the theme to green.
        colorBoard = ILI9341_GREENYELLOW,
        colorBackground = ILI9341_OLIVE,
        colorLine = 0x4228,
        colorText = 0x4228,
        colorButtons = 0xC695;
        menu_setup(colorBackground, colorText, colorButtons);
      }
      else if(flag == 3){ // Set the theme to yellow.
        colorBoard = 0xFF72,
        colorBackground = 0xFD26,
        colorLine = 0x6203,
        colorText = 0x6203,
        colorButtons = 0xFFF9;
        menu_setup(colorBackground, colorText, colorButtons);
      }
      else if(flag == 4){ // Set the theme to pink.
        colorBoard = 0xF71F,
        colorBackground = 0x8312,
        colorLine = 0x2867,
        colorText = 0x2867,
        colorButtons = 0xB4F7;
        menu_setup(colorBackground, colorText, colorButtons);
      }

      else if(flag == 5){ // Set game level to 1.
        startingBoard = board1;
        set_starting_board(startingBoard);

        // Level Blocks
        tft_fillRect(170, 130, 10, 10, colorText); //easy
        tft_fillRect(207, 130, 10, 10, colorButtons); //medium
        tft_fillRect(220, 130, 10, 10, colorButtons); //medium
        tft_fillRect(258, 130, 10, 10, colorButtons); //hard
        tft_fillRect(271, 130, 10, 10, colorButtons); //hard
        tft_fillRect(284, 130, 10, 10, colorButtons); //hard
      }
      else if(flag == 6){ // Set game level to 2.
        startingBoard = board2;
        set_starting_board(startingBoard);

        // Level Blocks
        tft_fillRect(170, 130, 10, 10, colorButtons); //easy
        tft_fillRect(207, 130, 10, 10, colorText); //medium
        tft_fillRect(220, 130, 10, 10, colorText); //medium
        tft_fillRect(258, 130, 10, 10, colorButtons); //hard
        tft_fillRect(271, 130, 10, 10, colorButtons); //hard
        tft_fillRect(284, 130, 10, 10, colorButtons); //hard
      }
      else if(flag == 7){ // Set game level to 3.
        startingBoard = board3;
        set_starting_board(startingBoard);

        // Level Blocks
        tft_fillRect(170, 130, 10, 10, colorButtons); //easy
        tft_fillRect(207, 130, 10, 10, colorButtons); //medium
        tft_fillRect(220, 130, 10, 10, colorButtons); //medium
        tft_fillRect(258, 130, 10, 10, colorText); //hard
        tft_fillRect(271, 130, 10, 10, colorText); //hard
        tft_fillRect(284, 130, 10, 10, colorText); //hard
      }
  }
}

void startGame(){
  int8_t flag = 1;

  while(flag != -1){ // While the user has not pressed the "Menu" Button
    reset_game();

    flag = 1;

    int8_t input = -1, savedInput = -1, x = 16, currentInputNumber = 0, timerCounter = 0;
    int16_t location = -1;

    input = game_button_detect();
    draw_buttons(colorBoard, colorBackground, colorLine, colorText, colorButtons);

    reset_timer(colorText);

    // Timer setup
    timer1_init();
    ta1 = tb1 = timer1_read();

    while(flag == 1){ // While the user has not pressed either the "Menu" or "Clear" button
      ta2 = tb2 = timer1_read();

      char c;

      if(uart1_rxrdy()){ // If the user has written something over UART.

        c = uart1_rxread();

        if(c >= '0' && c <= '6') { // If the user has entered a valid input, write the current input number on the screen.
          tft_setTextSize(6);
          tft_setTextColor(colorBackground);
          tft_setCursor(260, 100);
          tft_write(currentInputNumber);

          currentInputNumber = c;

          tft_setTextColor(colorText);
          tft_setCursor(260, 100);
          tft_write(currentInputNumber);
        }
      }

      // This if statement serves to debounce the user touch input. After doing its work, the user input is placed in 'location'.
      if (timer1_elapsed_ms(tb1, tb2) > 30) {

        input = game_button_detect();

        if(input == -1 && savedInput != -1)
            location = savedInput;

        savedInput = input;
        tb1 = tb2;
      }

      if (timer1_elapsed_ms(ta1, ta2) > 50) {

          uint8_t tickFctResult = 1;

          if(location == 36) // If the user has pressed the "clear" button set the flag so the board gets reset.
              flag = 0;
          else if(location == 37) // If the user has pressed the "Menu" button set the flag so the program will leave this function call.
              flag = -1;
          else
            tickFctResult = tickFct_GAME(currentInputNumber - '0', location, colorText, colorBoard); // Otherwise call the tick function of the game state machine.

          location = -1; // Reset 'location' so the input is not put into the state machine more than once.

          if(timerCounter++ >= 20 && tickFctResult){ // If one second has passed and the state machine is not in the victory state, increment the timer.
              increment_timer(colorText);
              timerCounter = 0;
          }

          ta1 = ta2;
      }
    }
  }
}
