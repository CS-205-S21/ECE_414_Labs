#ifndef GAME_H
#define GAME_H
#include <inttypes.h>

extern uint8_t tickFct_GAME(uint8_t number, int16_t location, unsigned short colorText,  unsigned short colorBoard);
extern void draw_number(uint8_t number, uint8_t location, unsigned short colorText,  unsigned short colorBoard);
extern uint8_t check_valid(uint8_t number, uint8_t location);
extern void set_starting_board(uint8_t *startingBoard);
extern void reset_game();


#endif
