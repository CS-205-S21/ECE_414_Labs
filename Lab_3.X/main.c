#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2
#pragma config FWDTEN = OFF, JTAGEN = OFF, FSOSCEN = OFF

#include <xc.h>
#include <inttypes.h>
#include "porta_in.h"
#include "portb_out.h"
#include "debounce.h"
#include "debounce_1.h"
#include "SM.h"

#include "timer1p.h"

main() {
  uint8_t in, sig;
  uint16_t out;

  uint16_t ta1, ta2, tb1, tb2;

  porta_in_init();
  portb_out_init();
  timer1_init();
  
  random = 0;

  ta1 = tb1 = timer1_read();

  for(;;){
    ta2 = tb2 = timer1_read();
    random++;
    
    in = porta_in_read();
    in = ~in;

    if (timer1_elapsed_ms(ta1, ta2) > 50) {
      sig = debounce(in & 0x01) | debounce_1(in & 0x02) << 1;
      
      ta1 = ta2;
    }
    
    if (timer1_elapsed_ms(tb1, tb2) > 100) {
      out = Tick_SM((sig & 0x02) >> 1, sig & 0x01);
      
      tb1 = tb2;
    }
    
    portb_out_write(out);
  }
}
