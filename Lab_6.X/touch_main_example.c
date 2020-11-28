
#include <xc.h>
#include <plib.h>
#include "config.h"
#include "TouchScreen.h"
#include "tft_master.h"
#include "tft_gfx.h"

#include "UART1.h"
#include "display_manager.h"
#include "timer1p.h"
#include "oc1_plib.h"

#include "ztimer4.h"
#include "ic1.h"

#define BUFFER_SIZE 30

int main(int argc, char** argv) {

  uint16_t rpm;
  uint16_t ta1, ta2, tb1, tb2; // Timervariables
  uint16_t targetSpeed = 1000;
  char buffer[BUFFER_SIZE], inputBuffer[BUFFER_SIZE];
  uint16_t bufferPosition = 0;

  oc1_init_plib(0x4444); // Output compare setup.
  SetDCOC1PWM(0x4444);

  ts_lcd_init(); // LCD setup.

  zTimerOn(); // Ztimer needed for input capture.
  zTimerSet(100);

  ic1_init(); // Setup input capature.
  INTEnableSystemMultiVectoredInt();

  uart1_init(9600); // UART setup.

  timer1_init(); // Timer 1 manages calling the LCD functions at the right times.
  ta1 = tb1 = timer1_read();

  setTargetSpeed(targetSpeed);

  PORTSetPinsDigitalOut(IOPORT_B, BIT_15);
  PORTSetBits(IOPORT_B, BIT_15);

  uint16_t temp = 0, temp2 = 0, temp3 = 0;

  for(;;){
    ta2 = tb2 = timer1_read();
    char c, command;
    uint16_t inputValue;

    if(uart1_rxrdy()){

      c = uart1_rxread();
      setNextUARTChar(c);
      buffer[bufferPosition++] = c;

      if(c == '\r'){ // User has entered a full command.
        sscanf(buffer, "%c %d", &command, &inputValue); // Save the user input in variables.

        int i;
        for(i = 0; buffer[i] != '\r'; i++){
          buffer[i] = 0;
        }
        bufferPosition = 0;

        if(command == 's'){
            targetSpeed = inputValue;
            setTargetSpeed(targetSpeed);
        }

        if(command == 'p')
          setKp(inputValue);
        if(command == 'i')
          setKi(inputValue);
        if(command == 'd')
          setKd(inputValue);
      }
    }

    if (timer1_elapsed_ms(ta1, ta2) > 100) { // Update text on the display.
      updateDisplayText(rpm);
      //updateDisplayText(temp);

      //PORTToggleBits(IOPORT_B, BIT_15);

      uint16_t newSpeed = tickFct_PID_SM((int16_t)targetSpeed, (int16_t)rpm);
      SetDCOC1PWM(newSpeed);

/*
      if(temp2++ > 10){
        if(rpm > targetSpeed)
            temp = temp - 1000;
        else
            temp = temp + 1000;

        temp2 = 0;
      }
      SetDCOC1PWM(temp);
*/

      ta1 = ta2;
    }

    if (timer1_elapsed_ms(tb1, tb2) > 10) { // Update graphical speed information on the display.
      updateDisplayGraphics(rpm);

      tb1 = tb2;
    }

    if (zTimerReadFlag()) {
      rpm = ic1_getrpm();

      //uint32_t pd_ticks, rpm_l;

      //pd_ticks = ic1_getperiod();
      //rpm_l = ((PBCLK/(1*256)) * 60) / pd_ticks;
      //rpm = (uint16_t) rpm_l;

      /*
        period = ic1_getperiod();
        sprintf(inputBuffer, "period: %6d\r\n", period);
        uart1_txwrite_str(inputBuffer);

        if (period != lastperiod) {
            lastperiod = period;
        }
      */
    }

  }

    return (EXIT_SUCCESS);
}
