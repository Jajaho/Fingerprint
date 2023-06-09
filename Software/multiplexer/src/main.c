#include "defines.h"

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h> // AVR device-specific IO definitions

#include "uart.h"
#include "multiplexer.h"

// stdio stream initialization by _FDEV_SETUP_RW
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

int main(void) {

    SET(DDR, BOARD_LED);
    SET(DDR, TTESTER_START);
    SET(DDR, TTESTER_RST);

    uart_init(); 
    // The default stdio streams stdin, stdout, and stderr are set up by using the existing static FILE stream objects.
    // allows to use the shorthand functions (e.g. printf() instead of fprintf())
    stdout = stdin = &uart_str;
    
    while (1) // main loop
    {
        SET(PORT, TTESTER_START);

        CLR(PORT, TTESTER_START);
    }
}