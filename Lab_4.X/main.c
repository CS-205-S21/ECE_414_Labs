#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2
#pragma config FWDTEN = OFF, JTAGEN = OFF, FSOSCEN = OFF

#include <xc.h>
#include <inttypes.h>
#include "uart1.h"
#include "ztimer.h"


#define NUM_ITERATIONS 100000
#define NUM_REPS 10

/*
main() {

  uart1_init(19200);

  uart1_txwrite_str("Hello, this is a greeting message.\nHayden Fisher\nDan Carroll\n\n");

  uart1_txwrite(7);

  for(;;){
    while(!uart1_rxrdy());

    char c = uart1_rxread();

    if(c >= 'a')
      c = c - ('a' - 'A');
    else
      c = c + ('a' - 'A');

    while(!uart1_txrdy());
    uart1_txwrite(c);
  }
}
*/

void main()
{
 uint32_t t1, t2;
 uint8_t buffer[64];

 uart1_init(9600);
 zTimerOn();


 uart1_txwrite_str("Performance Summary: Time per operation statistics\r\n");

 // Test multiplying bytes
 t1 = zTimerReadms();
 test_uint8_mult();
 t2 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 sprintf(buffer, "UINT8 MULT: %.06f us per operation\r\n",(double)(t2-t1)/(double)NUM_ITERATIONS /(double)NUM_REPS*1000.0);
 uart1_txwrite_str(buffer);

 // Test multiplying bytes
 t1 = zTimerReadms();
 test_uint8_div();
 t2 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 sprintf(buffer, "UINT8 DIV: %.06f us per operation\r\n",(double)(t2-t1)/(double)NUM_ITERATIONS /(double)NUM_REPS*1000.0);
 uart1_txwrite_str(buffer);

 // Test multiplying bytes
 t1 = zTimerReadms();
 test_uint8_add();
 t2 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 sprintf(buffer, "UINT8 ADD: %.06f us per operation\r\n",(double)(t2-t1)/(double)NUM_ITERATIONS /(double)NUM_REPS*1000.0);
 uart1_txwrite_str(buffer);

 // Test multiplying bytes
 t1 = zTimerReadms();
 test_uint8_sub();
 t2 = zTimerReadms();
 // Print timing result. Doubles OK here. Not time critical code.
 sprintf(buffer, "UINT8 SUB: %.06f us per operation\r\n",(double)(t2-t1)/(double)NUM_ITERATIONS /(double)NUM_REPS*1000.0);
 uart1_txwrite_str(buffer);

 while (1); // When done, wait forever.
}
