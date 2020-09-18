#include <xc.h>
#include <inttypes.h>

#include "debounce_1.h"

static enum DEB_States { DEB_OFF, DEB_MAYBE_ON, DEB_MAYBE_OFF, DEB_ON } DEB_State;

uint8_t debounce_1(uint8_t sig){
static uint8_t sig_d_1 = 0;

switch (DEB_State) {
  case DEB_OFF:
    if(sig)
      DEB_State = DEB_MAYBE_ON;
    else
      DEB_State = DEB_OFF;

  break;
  case DEB_MAYBE_ON:
    if(sig)
      DEB_State = DEB_ON;
    else
      DEB_State = DEB_OFF;

  break;
  case DEB_MAYBE_OFF:
    if(sig)
      DEB_State = DEB_ON;
    else
      DEB_State = DEB_OFF;

  break;
  case DEB_ON:
    if(sig)
      DEB_State = DEB_ON;
    else
      DEB_State = DEB_MAYBE_OFF;

  break;
}
switch (DEB_State) {
  case DEB_OFF:
    sig_d_1 = 0;
  break;
  case DEB_MAYBE_ON:
    sig_d_1 = 1;
  break;
  case DEB_MAYBE_OFF:
        sig_d_1 = 0;
  break;
  case DEB_ON:
    sig_d_1 = 1;
  break;
}



return sig_d_1;
}
