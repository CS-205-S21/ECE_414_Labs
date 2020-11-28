
#include <stdint.h>

#include <xc.h>

#include "timer1p.h"

#define PRESCALE 256

void timer1_init() {
  T1CON = 0x8030; // Timer 1 on, prescale=256
  TMR1 = 0;
}

uint16_t timer1_read() {
  return TMR1;
}

uint16_t inline ticks_to_ms(uint16_t dt) {
  return ((uint32_t)dt * PRESCALE) / (CLOCK_FREQ/1000);
}

uint16_t timer1_elapsed_ms (uint16_t t1, uint16_t t2 ) {
  if (t2 >= t1) {
    return ticks_to_ms(t2-t1);
  }
  else {
    return ticks_to_ms((uint32_t)(65536 + t2 - t1));
  }
}
