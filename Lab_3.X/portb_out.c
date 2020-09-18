#include <xc.h>
#include <inttypes.h>
//#include "portb_out.h"
void portb_out_init() {
  ANSELB = 0b00000000000000;
  TRISB = 0b00000000000000; // set all port pins as inputs

  //CNPUB = 0x1F; // enable internal pullups on all pins
}
void portb_out_write(uint16_t val)
{
// 0000 0000 0000 0000
// RB 0000 X000 0X00 0000

    PORTB = (val & 0x003F) | (val & 0x07C0) << 1 | (val & 0xF800) << 2;
    //PORTB = 0xFFFF;
}
