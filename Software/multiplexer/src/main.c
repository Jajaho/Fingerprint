#include "defines.h"

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h> // AVR device-specific IO definitions
#include <avr/delay.h> // Functions for busy-wait delay loops

#include "uart.h"
#include "multiplexer.h"

// stdio stream initialization by _FDEV_SETUP_RW
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);


int main(void) {
    uint8_t i;
    char buf[20], s[20];
    char meausurement[8];

    

    // Set all output pins
    SET(DDR, BOARD_LED);
    SET(DDR, START_BTN);
    SET(DDR, TTESTER_START);
    SET(DDR, TTESTER_RST);

    SET(PORT, TTESTER_START);

    while (1)
    {
        _delay_ms(100);
    }
    
    /*
    mux_init();

    uart_init(); 
    // The default stdio streams stdin, stdout, and stderr are set up by using the existing static FILE stream objects.
    // allows to use the shorthand functions (e.g. printf() instead of fprintf())
    stdout = stdin = &uart_str;

    _delay_ms(300);
    CLR(PORT, TTESTER_START);
    _delay_ms(300);
    SET(PORT, TTESTER_START);
    _delay_ms(1000);

    //printf_P(PSTR("Enter command: "));
    if (fgets(buf, sizeof buf - 1, stdin) == NULL) {
                SET(PORT, BOARD_LED);
                _delay_ms(1000);
                CLR(PORT, BOARD_LED);                       
    }  // fgets() reads string into internal buffer, returns NULL on error or when end of file occurs while no characters have been read.

    //if (tolower(buf[0]) == 'q')               // tolower() converts uppercase letters to lowercase
    //    return 0;


    if (sscanf(buf, "[RL]", s) > 0){
        fgets(meausurement, 8, buf);
    }
    */
}