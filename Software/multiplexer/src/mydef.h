#ifndef MYDEF_H_
#define MYDEF_H_


#define __AVR_ATmega328P__
#define F_CPU 16000000UL

#define BAUD 9600

// Pins //

#define BOARD_LED PB5

// ADG726 Multiplexer
// Chip Select (active low)
#define NCSA PD2
#define NCSB PD3
// Logic Control 
#define A0 PD4
#define A1 PD5
#define A2 PD6
#define A3 PD7

// MAKROS //

#define SETBIT(port, pin) (port |= (1 << pin))
#define CLRBIT(port, pin) (port &= ~(1 << pin))
#define BITSET(port, pin) (port&(1 << pin))

#define LED_ON() SETBIT(PORTB, BOARD_LED)
#define LED_OFF() CLRBIT(PORTB, BOARD_LED)

#endif /* STDDEF_H_ */