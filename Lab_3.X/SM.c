#include <xc.h>
#include <inttypes.h>
#include "SM.h"

static enum SM_STATES { SM_START, SM_RANDOM, SM_R_WIN, SM_L_WIN, SM_LEFT, SM_RIGHT, SM_INIT} SM_STATE;

uint8_t Tick_SM(uint8_t r_b, uint8_t l_b) {
  uint8_t static LED = 0, B = 0, count = 0, s, speedCount, speed;
  
   switch(SM_STATE) {
      case SM_START:
          SM_STATE = SM_RANDOM;
          break;
       
      case SM_RANDOM:
          SM_STATE = SM_INIT;
          break;

      case SM_R_WIN:
         if (count >= 0b110) {
            SM_STATE = SM_RANDOM;
         }
         else {
            SM_STATE = SM_R_WIN;
         }
         break;

      case SM_L_WIN:
         if (count >= 0b110) {
            SM_STATE = SM_RANDOM;
         }
         else {
            SM_STATE = SM_L_WIN;
         }
         break;

      case SM_LEFT:
         if (LED >= 1 && !l_b) {
            SM_STATE = SM_LEFT;
         }
         else if (LED == 1 && l_b) {
            SM_STATE = SM_RIGHT;
            speed++;
         }
         else if (LED != 1 && l_b || LED == 0) {
            SM_STATE = SM_R_WIN;
         }
         else {
            SM_STATE = SM_RANDOM;
         }
         break;

      case SM_RIGHT:
         if (LED == 8 && r_b) {
            SM_STATE = SM_LEFT;
            speed++;
         }
         else if (LED <= 8 && !r_b) {
            SM_STATE = SM_RIGHT;
         }
         else if (LED == 9 || LED != 8 && r_b) {
             SM_STATE = SM_L_WIN;
         }
         else {
            SM_STATE = SM_RANDOM;
         }
         break;

      case SM_INIT:
         if (!s && r_b) {
            SM_STATE = SM_LEFT;
         }
         else if (s && l_b) {
            SM_STATE = SM_RIGHT;
         }
         else {
            SM_STATE = SM_INIT;
         }
         break;

      default:
         SM_STATE = SM_RANDOM;
         break;
   }
   
   
   
   
   
   switch(SM_STATE) {
      case SM_RANDOM:
        s = random & 1;
        
        break;
      case SM_R_WIN:
        count++;

        B = (count & 0x1) << 7;
        break;
      case SM_L_WIN:
        count++;

        B = count & 0x1;

        break;
      case SM_LEFT:
        
        if(speed < 3){
            if(speedCount >= 3){
                LED--;
                speedCount = 0;
            }
            else
                speedCount++;
        }
        else if(speed >= 3 && speed < 6){
            if(speedCount >= 2){
                LED--;
                speedCount = 0;
            }
            else
                speedCount++;
        }
        else
            LED--;
            
        
        B = 0b1 << (LED-1);
        break;
      case SM_RIGHT:
        
        if(speed < 3){
            if(speedCount >= 3){
                LED++;
                speedCount = 0;
            }
            else
                speedCount++;
        }
        else if(speed >= 3 && speed < 6){
            if(speedCount >= 2){
                LED++;
                speedCount = 0;
            }
            else
                speedCount++;
        }
        else
            LED++;
          
        B = 0b1 << (LED-1);
        break;

      case SM_INIT:
        count = 0;
        speedCount = 0;
        speed = 0;

        if(s)
          LED = 1;
        else
          LED = 8;
        
        B = 0b1 << (LED-1);
      break;
   }

   return B;
}
