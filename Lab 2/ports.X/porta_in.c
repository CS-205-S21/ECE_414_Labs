#include <xc.h>
#include <inttypes.h>
#include "porta_in.h"
void porta_in_init() {
    ANSELA = 0b00000000;
    TRISA = 0xFF; // set all port pins as inputs
    CNPUA = 0xFF; // enable internal pullups on all pins

}
uint8_t porta_in_read() {

  uint8_t data;
  data = PORTA;
}
