#include "defines.h"

#include <stdint.h>
#include <stdio.h>

#include <avr/io.h>     // AVR device-specific IO definitions
#include <avr/delay.h>  // Functions for busy-wait delay loops
#include <avr/interrupt.h> // Interrupts handling

#include "uart.h"
#include "multiplexer.h"

// stdio stream initialization by _FDEV_SETUP_RW
FILE uart_str = FDEV_SETUP_STREAM(uart_putchar, uart_getchar, _FDEV_SETUP_RW);

uint8_t channel = 0;

int main(void) {
    
    //uint8_t i;
    //char buf[40], s[40];
    //char meausurement[8];

     

    // -------- Inits --------- //

    // Pin Change Interrupt Control Register

    PCICR |= (1 << PCIE0);              // Enable Pin Change Interrupt 0 
    PCMSK0 |= (1 << PCINT2);            // Enable PCINT2 (PB2) for Pin Change Interrupt 0 (Start Button)

    PCICR |= (1 << PCIE1);              // Enable Pin Change Interrupt 1
    PCMSK1 |= (1 << PCINT11);           // Enable PCINT11 (PC3) for Pin Change Interrupt 1
    PCMSK1 |= (1 << PCINT12);           // Enable PCINT12 (PC4) for Pin Change Interrupt 1
    PCMSK1 |= (0 << PCINT13);           // Enable PCINT13 (PC5) for Pin Change Interrupt 1


    // Set pins as output
    SET(DDR, TTESTER_NSTART);
    SET(DDR, TTESTER_NRST);
    SET(DDR, BOARD_LED);
    SET(DDR, PCB_LED);

    // Set pins as input
    CLR(DDR, NSTART_BTN);
    CLR(DDR, NSWITCH_1);
    CLR(DDR, NSWITCH_2);
    CLR(DDR, NSWITCH_3);

    // Active pull-up resistors
    SET(PORT, NSTART_BTN);
    SET(PORT, NSWITCH_1);
    SET(PORT, NSWITCH_2);
    SET(PORT, NSWITCH_3);

    // Set initial I/O state of ttester com-pins
    SET(PORT, TTESTER_NSTART);
    SET(PORT, TTESTER_NRST);

    
    mux_init();
    // uart_init(); 


    
    // -------- Main Program -------- //
    


    mux_set_channel('D', 1);    // Set both channels to physcial numbner 1 
    mux_enable();

    SET(PORT, PCB_LED);
    CLR(PORT, PCB_LED);

    CLR(PORT, TTESTER_NRST);
    SET(PORT, TTESTER_NRST);

    _delay_ms(1000);

    //CLR(PORT, TTESTER_NSTART);
    //_delay_ms(300);
    //SET(PORT, TTESTER_NSTART);

    SET(PORT, PCB_LED);
    _delay_ms(300);
    CLR(PORT, PCB_LED);
    _delay_ms(300);

    sei();  // Enable global interrupts

    while (1)
    { 
        if (channel == 1)
        {
            SET(PORT, BOARD_LED);
            _delay_ms(200);
            CLR(PORT, BOARD_LED);
        }
        _delay_ms(100);
    }

    /*
    // The default stdio streams stdin, stdout, and stderr are set up (using the same buffer) by using the existing static FILE stream objects.
    // allows to use the shorthand functions (e.g. printf() instead of fprintf())
    stdout = stdin = &uart_str;
    
   while (1)
    {
        
        
        // Reads string into internal buffer, returns NULL on error or when end of file occurs while no characters have been read.
        if (fgets(buf, sizeof buf - 1, &uart_str) != NULL) {
                    SET(PORT, BOARD_LED);
                    _delay_ms(100);
                    CLR(PORT, BOARD_LED);                       
        }  
        
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
        
        SET(PORT, BOARD_LED);
        _delay_ms(200);
        CLR(PORT, BOARD_LED);
        _delay_ms(200);
        SET(PORT, BOARD_LED);
        _delay_ms(200);
        CLR(PORT, BOARD_LED);
        _delay_ms(1000);
    }
    */
}

ISR(PCIE0_vect) {
    SET(PORT, PCB_LED);
    CLR(PORT, TTESTER_NSTART);

    _delay_ms(300);

    SET(PORT, TTESTER_NSTART);
    CLR(PORT, PCB_LED);
}

ISR(PCIE1_vect) {
    channel = (uint8_t) PORTC & 0b00111000;     // Read NSWITCH_1, NSWITCH_2 and NSWITCH_3 (LSB is switch 1, MSB is switch 3)

}