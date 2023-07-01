#include "defines.h"

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>     // AVR device-specific IO definitions
#include <avr/delay.h>  // Functions for busy-wait delay loops

#include "uart.h"
#include "multiplexer.h"

// stdio stream initialization by _FDEV_SETUP_RW
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);


int main(void) {
    uint8_t i;
    char buf[40], s[40];
    char meausurement[8];

    // -------- Inits --------- //

    // Set pins as output
    SET(DDR, TTESTER_NSTART);
    SET(DDR, TTESTER_NRST);

    // Set pins as input
    CLR(DDR, BOARD_LED);
    CLR(DDR, START_BTN);

    // Set initial I/O state
    SET(PORT, TTESTER_NSTART);
    SET(PORT, TTESTER_NRST);

    mux_init();
    uart_init(); 

    // The default stdio streams stdin, stdout, and stderr are set up (using the same buffer) by using the existing static FILE stream objects.
    // allows to use the shorthand functions (e.g. printf() instead of fprintf())
    stdout = stdin = &uart_str;

    // -------- Main Program -------- //


    mux_set_channel('D', 1);
    mux_enable();

    CLR(PORT, TTESTER_NRST);
    _delay_ms(300);
    SET(PORT, TTESTER_NRST);

    _delay_ms(1000);

    CLR(PORT, TTESTER_NSTART);
    _delay_ms(300);
    SET(PORT, TTESTER_NSTART);

   while (1)
    {
        
        
        // Reads string into internal buffer, returns NULL on error or when end of file occurs while no characters have been read.
        if (fgets(buf, sizeof buf - 1, stdin) == NULL) {
                    SET(PORT, BOARD_LED);
                    _delay_ms(1000);
                    CLR(PORT, BOARD_LED);                       
        }  
        /*
        //if (tolower(buf[0]) == 'q')               // tolower() converts uppercase letters to lowercase
        //    return 0;

        
        if (sscanf(buf, "O", s) > 0){
            //fgets(meausurement, 8, buf);
            SET(PORT, BOARD_LED);
            _delay_ms(1000);
        } 
        else {
            SET(PORT, BOARD_LED);
            _delay_ms(200);
        }
        CLR(PORT, BOARD_LED);
        _delay_ms(1000);
        */
        SET(PORT, BOARD_LED);
        _delay_ms(200);
        CLR(PORT, BOARD_LED);
        _delay_ms(200);
        SET(PORT, BOARD_LED);
        _delay_ms(200);
        CLR(PORT, BOARD_LED);
        _delay_ms(1000);
    }
}