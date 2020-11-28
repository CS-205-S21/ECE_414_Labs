#include <xc.h>
#include <inttypes.h>
#include "tft_master.h"
#include "tft_gfx.h"
#include "game.h"

static enum GAME_STATES { GAME_START, GAME_INIT, GAME_WAIT_FOR_INPUT, GAME_CHECK_INPUT, GAME_ERROR, GAME_CHECK_FOR_WIN, GAME_VICTORY} GAME_STATE, NEXT_STATE;

#define X_DIST_BETWEEN_NUMS 38
#define Y_DIST_BETWEEN_NUMS 38
#define BOARD_SIZE 36
#define GAME_BOX_SIZE 6
#define GAME_ROW_SIZE 6
#define GAME_COLUMN_SIZE 6

uint8_t gameStart [BOARD_SIZE];
uint8_t board [BOARD_SIZE];
const int16_t pattern[8] = {BIT_4, BIT_5, BIT_7, BIT_8, BIT_9, BIT_10, BIT_13, BIT_15};


// The tick function of the GAME state machine.
// Returns 0 if the state machine is in the GAME_VICTORY state, returns 1 otherwise.
uint8_t tickFct_GAME(uint8_t number, int16_t location, unsigned short colorText, unsigned short colorBoard) {
  static uint8_t valid = 0;
  static uint8_t errorCount = 0;
  static uint8_t victoryCount = 0, victoryCount2 = 0;
  static uint8_t savedNumber;
  static int16_t savedLocation;

  uint8_t victory, i;

   // Next state logic. Determines which state the state machine will be in next tick.
   switch(GAME_STATE) {

     case GAME_START:
        NEXT_STATE = GAME_INIT;
        break;

      case GAME_INIT:
         NEXT_STATE = GAME_WAIT_FOR_INPUT;
         break;

      // The state machine will remain in this state until a valid input is input into the machine (There is a valid input if 'location' is a value other than -1).
      case GAME_WAIT_FOR_INPUT:
         if(location == -1)
            NEXT_STATE = GAME_WAIT_FOR_INPUT;
         else
            NEXT_STATE = GAME_CHECK_INPUT;
         break;

      // If the input is invalid (if the input number is already in the same box, row, or column as the input) move to the error state. Otherwise, check for a victory.
      case GAME_CHECK_INPUT:
            if(check_valid(savedNumber, savedLocation))
              NEXT_STATE = GAME_CHECK_FOR_WIN;
            else
              NEXT_STATE = GAME_ERROR;
         break;

      // The user has tried to enter something wrong, stay in the error state for 20 ticks then return to waiting for input.
      case GAME_ERROR:
        if(errorCount < 20){
            NEXT_STATE = GAME_ERROR;
        }else
            NEXT_STATE = GAME_WAIT_FOR_INPUT;
        break;

      case GAME_CHECK_FOR_WIN:

          victory = 1;

          // Loop through every board space. If there are no 0's that means the user has won and we need to go to the victory state.
          for(i = 0; i < BOARD_SIZE; i++)
              if(board[i] == 0){
                victory = 0;
              }

          if(victory)
            NEXT_STATE = GAME_VICTORY;
          else
            NEXT_STATE = GAME_WAIT_FOR_INPUT;
         break;

      // Once in the victory state, stay there. The only way to leave is for the user to press the "Menu" button which has an effect a level up in "touch_main_example.c".
      case GAME_VICTORY:
           NEXT_STATE = GAME_VICTORY;
        break;

      // This should never happen.
      default:
          NEXT_STATE = GAME_INIT;
         break;
   }

// ------------------------------------------------------------------------------------------------------

  // Current state logic.
  switch(GAME_STATE) {
      case GAME_START:
         break;

       // When in the INIT state, reset the whole board.
       case GAME_INIT:
          victoryCount = 0;
          for(i = 0; i < BOARD_SIZE; i++){
            board[i] = gameStart[i];
            draw_number(board[i], i, colorText, colorBoard);
          }

          break;

       case GAME_WAIT_FOR_INPUT:
          errorCount = 0; // This needs to be reset here in case we move to the error state.
          savedNumber = number; // If the user gives some input, save that input to these variables so in can be processed.
          savedLocation = location;
          break;

       // If the user input is valid, draw the input in the place where it should go.
       case GAME_CHECK_INPUT:
          if(check_valid(savedNumber, savedLocation)){
            draw_number(savedNumber, savedLocation, colorText, colorBoard);
            board[savedLocation] = savedNumber;
          }
          break;

       // If the user entered a wrong input, blink two of the LED's to indicate their mistake.
       case GAME_ERROR:
            errorCount++;

            if(errorCount >= 10)
              PORTClearBits(IOPORT_B, BIT_4 | BIT_5);
            else
              PORTToggleBits(IOPORT_B, BIT_4 | BIT_5);
         break;

       case GAME_CHECK_FOR_WIN:
          break;

       // If the user has won, display victory text and play the light show.
       case GAME_VICTORY:

           if(victoryCount2++ >= 4){
              victoryCount++;
              victoryCount2 = 0;
           }

           if(victoryCount == 1 && victoryCount2 == 1){ // Display victory text.
             tft_fillRect(35, 95, 240, 45, ILI9341_BLACK);
             tft_setTextSize(5);
             tft_setTextColor(ILI9341_WHITE);
             tft_setCursor(40, 100);
             tft_writeString("VICTORY!");
           }

           if(victoryCount >= 32){
             PORTClearBits(IOPORT_B, BIT_4 | BIT_5 | BIT_7 | BIT_8 | BIT_9 | BIT_10 | BIT_13 | BIT_15);
           }
           else if(victoryCount < 8){
              PORTSetBits(IOPORT_B, pattern[victoryCount]);
           }
           else if(victoryCount >= 8 && victoryCount < 16){
              PORTClearBits(IOPORT_B, BIT_4 | BIT_5 | BIT_7 | BIT_8 | BIT_9 | BIT_10 | BIT_13 | BIT_15);
              PORTSetBits(IOPORT_B, pattern[victoryCount - 8]);
           }
           else if(victoryCount >= 16 && victoryCount < 24){
              PORTSetBits(IOPORT_B, pattern[7 - (victoryCount - 16)]);
           }
           else if(victoryCount >= 24 && victoryCount < 32){
              PORTClearBits(IOPORT_B, BIT_4 | BIT_5 | BIT_7 | BIT_8 | BIT_9 | BIT_10 | BIT_13 | BIT_15);
              PORTSetBits(IOPORT_B, pattern[7 - (victoryCount - 24)]);
           }

           return 0;

         break;

       default:
          break;
      }

      GAME_STATE = NEXT_STATE;
      return 1;
   }

// Draws 'number' at 'location' on the board using 'colorText'. If 'number' == 0 the function erases the old number and leaves the space blank.
void draw_number(uint8_t number, uint8_t location, unsigned short colorText, unsigned short colorBoard){

    uint8_t x, y;

    x = location % 6; // Determine the x,y values of location. See documentation for the chart defining location.
    y = location / 6;

    // Clear the old space on the board.
    tft_setTextSize(2);
    tft_setTextColor(colorBoard);
    tft_setCursor( x * X_DIST_BETWEEN_NUMS + 20,  y * Y_DIST_BETWEEN_NUMS + 20);
    tft_write(board[location] + '0');

    // If number is not zero, put the new number in the space.
    if(number != 0){
      tft_setTextColor(colorText);
      tft_setCursor( x * X_DIST_BETWEEN_NUMS + 20,  y * Y_DIST_BETWEEN_NUMS + 20);
      tft_write(number + '0');
    }
}

// Returns 1 if 'number' is not already present in the same box, row, or column that 'location' belongs to.
uint8_t check_valid(uint8_t number, uint8_t location){

  uint8_t i;

  if(number == 0){
    if(gameStart[location] != 0) // If the input is trying to override a locked preset value on the start board.
      return 0;
  }
  else {
      if(gameStart[location] != 0) // If the input is trying to override a locked preset value on the start board.
        return 0;

      // These two arrays are used below to quickly check all the values in a box for a matching value.
      const uint8_t boxIndex[BOARD_SIZE] = { 0, 0, 0, 1, 1, 1,
                                       0, 0, 0, 1, 1, 1,
                                       2, 2, 2, 3, 3, 3,
                                       2, 2, 2, 3, 3, 3,
                                       4, 4, 4, 5, 5, 5,
                                       4, 4, 4, 5, 5, 5};
      const uint8_t box[6][6] = { {0,  1,  2,  6,  7,  8},
                            {3,  4,  5,  9,  10, 11},
                            {12, 13, 14, 18, 19, 20},
                            {15, 16, 17, 21, 22, 23},
                            {24, 25, 26, 30, 31, 32},
                            {27, 28, 29, 33, 34, 35},};

      // Cycles through each of the six spots and returns 0 if 'number' is already in one of those spots.
      for(i = 0; i < GAME_BOX_SIZE; i++){
          if( board[ box[ boxIndex[location] ][i] ] == number)
            return 0;
      }

      uint8_t x, y;

      x = location % 6;
      y = location / 6;

      // Cycles through each of the six row spots in the same row as 'location' and returns 0 if 'number' is in that row already.
      for(i = 0; i < GAME_ROW_SIZE; i++){
          if( board[ (y * 6) + i] == number)
            return 0;
      }

      // Cycles through each of the six column spots in the same column as 'location' and returns 0 if 'number' is in that column already.
      for(i = 0; i < GAME_COLUMN_SIZE; i++){
          if( board[ x + (i * 6)] == number)
            return 0;
      }
    }

  return 1;
}

void set_starting_board(uint8_t *startingBoard){
    uint8_t i;

    for(i = 0; i < BOARD_SIZE; i++){
        gameStart[i] = *(startingBoard + i);
    }
}

void reset_game(){
      GAME_STATE = GAME_START;
}
