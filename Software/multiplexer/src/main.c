#include "mydef.h"
#include <stddef.h>
#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>  

int main(void) {

    DDRB = (1 << BOARD_LED);
    PORTB = (1 << BOARD_LED);
    //uart_init(); 
    
    while (1) // main loop
    {
        //uart_gets(&string, 9);
        //uart_puts(&string);
    }
}