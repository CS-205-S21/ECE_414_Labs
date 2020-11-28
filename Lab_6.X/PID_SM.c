#include <xc.h>
#include <inttypes.h>
#include "PID_SM.h"

static enum PID_STATES { PID_SMStart, PID_INIT, PID_CONTROL} PID_STATE;
  int16_t Kp;
  int16_t Ki;
  int16_t Kd;

void setKp(int16_t newKp){
  Kp = newKp;
}

void setKi(int16_t newKi){
  Ki = newKi;
}

void setKd(int16_t newKd){
  Kp = newKd;
}

uint16_t tickFct_PID_SM(int16_t desired, int16_t actual) {
  static int32_t actuator;
  static int32_t actual_prev;
  int32_t error;
  int32_t derivative, Sp, Sd, Si;
  static int32_t integral;

   switch(PID_STATE) {
      case PID_INIT:
         PID_STATE = PID_CONTROL;
         break;
      case PID_CONTROL:
         PID_STATE = PID_CONTROL;
         break;
      default:
         PID_STATE = PID_INIT;
         break;
   }

   switch(PID_STATE) {
      case PID_INIT:
         actuator = 0;
         actual_prev = 0;
         break;
      case PID_CONTROL:

         error = (int16_t)desired - (int16_t)actual;
         derivative = actual - actual_prev;
         integral = integral + error;

         Sp = Kp*error;
         Si = Ki*integral;
         Sd = Kd*derivative;

         actuator = Sp + Si - Sd;
         actual_prev = actual;

         if(actuator > 0xFFFF)
            return 0xFFFF;
         else if(actuator < 0)
            return 0;

         //actuator = Kp*error + Ki*integral - Kd*derivative;
         //actuator = Kp*error;
/*
         *temp = desired;

         error = desired - actual;
         actuator = actuator + Kp*error;
         actual_prev = actual;

         */
         break;
   }

   return (uint16_t)actuator;
}
