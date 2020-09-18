#include <xc.h>
#include <inttypes.h>

#include "debounce.h"

static enum DEB_States { DEB_OFF, DEB_MAYBE_ON, DEB_MAYBE_OFF, DEB_ON } DEB_State;

uint8_t debounce(uint8_t sig){
static uint8_t sig_d = 0;

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
    sig_d = 0;
  break;
  case DEB_MAYBE_ON:
    sig_d = 1;
  break;
  case DEB_MAYBE_OFF:
        sig_d = 0;
  break;
  case DEB_ON:
    sig_d = 1;
  break;
}



return sig_d;
}
