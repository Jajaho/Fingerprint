#ifndef DEFINES_H_
#define DEFINES_H_


#define __AVR_ATmega328P__

// ----- CPU Clock Speed & BAUD ----- //
// required for util/setbaud.h
#define F_CPU 16000000UL
#define BAUD 9600

// ----- Pin Definitions ----- //
// for DualMetroPrototype V1.0 

#define BOARD_LED B, 5
#define PCB_LED C, 0

#define NSTART_BTN B, 2

#define NSWITCH_1 C, 3
#define NSWITCH_2 C, 4
//#define NSWITCH_3 C, 5

#define TTESTER_NMC C, 5

#define TTESTER_NSTART C, 1		// Not Start
#define TTESTER_NRST C, 2		// Not Reset

// ----- ADG726 Multiplexer ------ //

// State Control (active low) //
#define ADG726_NEN D, 2     // Not Enable
#define ADG726_NWR D, 3     // Not Write Enable

// Chip Select (active low) //
#define ADG726_NCSA B, 0    // Not Chip Select A
#define ADG726_NCSB B, 1    // Not Chip Select B

// Logic Control 
// active high, should all be on the same port with ascending pin numbers
#define ADG726_A0 D, 4     
#define ADG726_A1 D, 5
#define ADG726_A2 D, 6
#define ADG726_A3 D, 7

// ----- MAKROS ----- //

// Hannes MAKROS //
#define SETBIT(port, pin) (port |= (1 << pin))
#define CLRBIT(port, pin) (port &= ~(1 << pin))
#define BITSET(port, pin) (port&(1 << pin))

#define LED_ON() SETBIT(PORTB, BOARD_LED)
#define LED_OFF() CLRBIT(PORTB, BOARD_LED)


// AVR LIBC MAKROS //
// See: https://www.nongnu.org/avr-libc/examples/stdiodemo/hd44780.c

#define GLUE(a, b) a##b //Conactenates two tokens

/* single-bit macros, used for control bits */
#define SET_(what, p, m) GLUE(what, p) |= (1 << (m))
#define CLR_(what, p, m) GLUE(what, p) &= ~(1 << (m))
#define GET_(/* PIN, */ p, m) GLUE(PIN, p) & (1 << (m))
#define SET(what, x) SET_(what, x)
#define CLR(what, x) CLR_(what, x)
#define GET(/* PIN, */ x) GET_(x)

/* multy-bit macros, used to read or write entire registers */

/// ASSIGN(PORT, FIRST_BIT, DATA) The data bits have to be in consequtive ascending order
#define ASSIGN_(what, p, m, v) GLUE(what, p) = (GLUE(what, p) & \
						~((1 << (m)) | (1 << ((m) + 1)) | \
						  (1 << ((m) + 2)) | (1 << ((m) + 3)))) | \
					        ((v) << (m)) 
#define READ_(what, p, m) (GLUE(what, p) & ((1 << (m)) | (1 << ((m) + 1)) | \
					    (1 << ((m) + 2)) | (1 << ((m) + 3)))) >> (m)
#define ASSIGN(what, x, v) ASSIGN_(what, x, v)
#define READ(what, x) READ_(what, x)


#endif /* DEFINES_H_ */