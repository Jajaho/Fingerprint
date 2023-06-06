#include "stddef.h"
#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>  

int main(void) {

    DDRB = (1 << PB5);
    uart_init(); 
    char string[9] = "";
    
    while (1) // main loop
    {
        uart_gets(&string, 9);
        uart_puts(&string);
    }
}