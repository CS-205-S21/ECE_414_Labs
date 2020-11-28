/*
 * File:   oc1_plib.h
 * Author: nestorj
 * Functions are identical to the SFR version except for the "_plib" suffix
 * Module to configure & control OC1 using timer 3 with PLIB
 *
 * Created on September 26, 2019, 2:48 PM
 */

#ifndef OC1_H
#define	OC1_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <inttypes.h>

    // initialize output compare using timer3
    extern void oc1_init_plib(uint16_t duty);

    // set duty cycle 0x0000-0xffff
    extern void oc1_setduty_plib(uint16_t duty);


#ifdef	__cplusplus
}
#endif

#endif	/* OC1_H */
