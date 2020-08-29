#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2
#pragma config FWDTEN = OFF, JTAGEN = OFF, FSOSCEN = OFF

#include <xc.h>
#include <inttypes.h>
#include "porta_in.h"
#include "portb_out.h"
main() {
 uint8_t in;
 uint16_t out;
 porta_in_init();
 portb_out_init();
 while (1) {
  in = porta_in_read();

  out = 0b1 << (in & 0x0F);

  if((in & 0x10) == 0x10)
    out = ~out;

  portb_out_write(out);
 }
}
