#include <xc.h>
#include <inttypes.h>
#include "calculator.h"

static enum CALC_STATES { CALC_SMStart, CALC_INIT, CALC_OPERAND1, CALC_OPERATOR, CALC_OPERAND2, CALC_EQUALS, CALC_ERROR, CALC_RESULT, CALC_DIVZERO} CALC_STATE, NEXT_STATE;


int64_t tickFct_CALCULATOR(uint8_t button) {
    static int32_t memory, currentNum, operator, newOperator;

   switch(CALC_STATE) {
      case CALC_SMStart:
         NEXT_STATE = CALC_INIT;
         break;

      case CALC_INIT:
         NEXT_STATE = CALC_OPERAND1;
         break;

      case CALC_OPERAND1:
         if(button == 14) // If C is pressed.
            NEXT_STATE = CALC_INIT;
         else if(button >= 10 && button <= 13) // If an operator has been pressed.
            NEXT_STATE = CALC_OPERAND2;
         else if( (currentNum > 0x10000000 && currentNum * 10 + button < 0x10000000)) // If adding this number will  cause overflow
            NEXT_STATE = CALC_ERROR;
         else
            NEXT_STATE = CALC_OPERAND1;
         break;

      case CALC_OPERATOR:
            if(newOperator == 13 && currentNum == 0)
              NEXT_STATE = CALC_DIVZERO;
            else
              NEXT_STATE = CALC_OPERAND2;
         break;

      case CALC_OPERAND2:
        if(button == 14) // If C is pressed.
           NEXT_STATE = CALC_INIT;
        else if(button >= 10 && button <= 13) // If an operator has been pressed.
           NEXT_STATE = CALC_OPERATOR;
        else if( (currentNum > 0x10000000 && currentNum * 10 + button < 0x10000000)) // If adding this number will  cause overflow
           NEXT_STATE = CALC_ERROR;
        else if(button == 15) // If = is pressed.
           NEXT_STATE = CALC_EQUALS;
        else
           NEXT_STATE = CALC_OPERAND2;
        break;

      case CALC_EQUALS:
          if(newOperator == 13 && currentNum == 0)
            NEXT_STATE = CALC_DIVZERO;
          else
            NEXT_STATE = CALC_RESULT;
         break;

      case CALC_RESULT:
        if(button == 14) // If C is pressed.
          NEXT_STATE = CALC_INIT;
        else
          NEXT_STATE = CALC_RESULT;
      break;

      case CALC_ERROR:
        if(button == 14) // If C is pressed.
          NEXT_STATE = CALC_INIT;
        else
          NEXT_STATE = CALC_ERROR;
        break;

      case CALC_DIVZERO:
        if(button == 14) // If C is pressed.
          NEXT_STATE = CALC_INIT;
        else
          NEXT_STATE = CALC_DIVZERO;
        break;

      default:
          NEXT_STATE = CALC_INIT;
         break;
   }

// ------------------------------------------------------------------------------------------------------

   switch(CALC_STATE) {
      case CALC_SMStart:
         break;
      case CALC_INIT:
         memory = 0;
         currentNum = 0;
         operator = 0;
         break;
      case CALC_OPERAND1:
        if(button < 10) // If a number has been pressed.
          if( !(currentNum > 0x10000000 && currentNum * 10 + button < 0x10000000)) // If adding this number will not cause overflow, add it.
            currentNum = currentNum * 10 + button;

        if(button >= 10 && button <= 13){ // If an operator has been pressed.
            operator = button;
            memory = currentNum;
            currentNum = 0;
        }

         break;
      case CALC_OPERATOR:
        if(memory == 0){ // If the memory is blank.
          memory = currentNum;
        }
        else{
          if(operator == 10) // +
            memory = memory + currentNum;
          else if(operator == 11) // -
            memory = memory - currentNum;
          else if(operator == 12) // x
            memory = memory * currentNum;
          else if(operator == 13 && currentNum != 0) // /
            memory = memory / currentNum;
        }

        currentNum = 0;
        operator = newOperator;

        break;
      case CALC_OPERAND2:
        if(button < 10){ // If a number has been pressed.
          if( !(currentNum > 0x10000000 && currentNum * 10 + button < 0x10000000)) // If adding this number will not cause overflow, add it.
            currentNum = currentNum * 10 + button;
        }

        if(button >= 10 && button <= 13) // If an operator has been pressed.
        {
            newOperator = button;

        }

        break;
         
      case CALC_EQUALS:

        if(operator == 10) // +
          currentNum = memory + currentNum;
        else if(operator == 11) // -
          currentNum = memory - currentNum;
        else if(operator == 12) // x
          currentNum = memory * currentNum;
        else if(operator == 13 && currentNum != 0) // /
          currentNum = memory / currentNum;

         break;

      case CALC_ERROR:
        currentNum = -1001;
         break;

       case CALC_DIVZERO:
         currentNum = -1002;
          break;

      default:
         break;
   }
   
   CALC_STATE = NEXT_STATE;
   return currentNum;
}
