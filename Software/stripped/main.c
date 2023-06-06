#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>
#include <stdlib.h>
#include <string.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <math.h>

#define MAIN_C
#include "Transistortester.h"

#ifndef INHIBIT_SLEEP_MODE
    // prepare sleep mode
    EMPTY_INTERRUPT(TIMER2_COMPA_vect);
#endif
    #if !defined(INHIBIT_SLEEP_MODE) || defined(SamplingADC)
    // ADC_vect is always required by samplingADC()
    EMPTY_INTERRUPT(ADC_vect);
    #endif

//begin of transistortester program
int main(void) {
    uint8_t ii;
    unsigned int max_time;
    uint8_t vak_diode_nr;		// number of the protection diode of BJT
    union {
    uint16_t pw;
    uint8_t pb[2];
    } rpins;
    uint8_t x, y, z;
    //switch on
    ON_DDR = (1<<ON_PIN);			// switch to output
    ON_PORT = (1<<ON_PIN); 		// switch power on 





    // Welche TP sind am multiplexer angeschlossen?
    EntladePins();		// discharge capacities
    //measurement of capacities in all 3 combinations
    ReadCapacity(TP3, TP1);





    if (PartFound == PART_CAPACITOR) {
        #if FLASHEND > 0x3fff
            if ((cap.ca + cap.cb) == (TP1 + TP3)) {
                show_Cap13();		// repeated capacity measurement
                goto shut_off;		// key was pressed or timeout
            }
            show_cap(0);		// show capacity in normal way and measure additional parameters
            #else
                show_cap_simple();		// show capacity in normal way and measure additional parameters
            #endif
        goto tt_end;
    } /* end PartFound == PART_CAPACITOR */
    
    
    
    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - 
    tt_end:
    #if POWER_OFF+0 > 1
        empty_count = 0;		// reset counter, if part is found
        mess_count++;			// count measurements
    #endif
    max_time = display_time;	// full specified wait time

    end2:
    ADC_DDR = (1<<TPRELAY) | TXD_MSK; 	// switch pin with reference to GND, release relay
    lcd_refresh();			// write the pixels to display, ST7920 only
    while (!(RST_PIN_REG & (1 << RST_PIN)))
    ;	//wait ,until button is released

    ii = wait_for_key_ms(max_time);
    #if POWER_OFF+0 > 1
        #ifdef WITH_ROTARY_SWITCH
            if ((ii > 0) || (rotary.incre > 0))
            #else
            if (ii > 0)
            #endif
            {
        empty_count = 0;		// reset counter, if any switch activity
        mess_count = 0; }
    #endif

if (ii != 0)
    goto loop_start;
    // key is pressed again, repeat measurement
    shut_off:
    // look, if the tester is uncalibrated (C-source will be included directly)
    lcd_cursor_off();
    //#include "HelpCalibration.c"
#endif
goto loop_start;
// POWER_OFF not selected, repeat measurement
//  return 0;
}