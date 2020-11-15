#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H
#include <inttypes.h>

extern void setTargetSpeed(uint16_t targetSpeed);

extern void setNextUARTChar(char c);

extern void updateDisplayText(uint16_t currentSpeed);

extern void updateDisplayGraphics(uint16_t currentSpeed);

#endif
