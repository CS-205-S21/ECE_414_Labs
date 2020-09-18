#include <stdint.h>

#ifndef TIMER1P_H

#define TIMER1P_H

#define CLOCK_FREQ 40000000

extern void timer1_init();

extern uint16_t timer1_read();

extern uint16_t timer1_elapsed_ms(uint16_t t1, uint16_t t2 );

#endif
/* TIMER1P_H */
