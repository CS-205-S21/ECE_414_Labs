#ifndef BUTTON_MANAGER_H
#define BUTTON_MANAGER_H

extern void draw_buttons();
extern int8_t game_button_detect();
extern int8_t draw_buttons(unsigned short colorBoard,
                  unsigned short colorBackground,
                  unsigned short colorLine,
                  unsigned short colorText,
                  unsigned short colorButtons);

#endif
