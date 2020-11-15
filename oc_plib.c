/*
 * File:   oc1.c
 * Author: nestorj
 *
 * Module to configure & control OC1 using timer 3 - SFR Version
 * Created on September 26, 2019, 2:48 PM
 */

#include "oc1_plib.h"
#include <xc.h>
#include <plib.h>

    void oc1_init_plib(uint16_t duty) {
        OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, 0xffff);
        OpenOC1(OC_ON | OC_TIMER_MODE16| OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE,
                duty, duty);
        // only OC1RS (2rd arg) matters in this example
        PPSOutput(1, RPA0, OC1);  // map to RPA0 (pin 2)
    }

    void oc1_setduty_plib(uint16_t duty) {
        SetDCOC1PWM(duty);
    }
