#include "defines.h"
//#include <stddef.h>

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h> // AVR device-specific IO definitions
#include <util/setbaud.h>

#include "uart.h"
#include "multiplexer.h"

int main(void) {

    SETBIT(DDRB, BOARD_LED);
    SETBIT(PORTB, BOARD_LED);
    uart_init(); 
    
    while (1) // main loop
    {
        //uart_gets(&string, 9);
        //uart_puts(&string);
    }
}