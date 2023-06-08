/// ADG726 Multiplexer
#ifndef ADG726_H   
    #define ADG726_H
    
    // State Control (active low) //
    #define NEN PD2     // Not Enable
    #define NWR PD3     // Not Write Enable
    // Chip Select (active low) //
    #define NCSA PB0    // Not Chip Select A
    #define NCSB PB1    // Not Chip Select B
    // Logic Control (active high) //
    #define A0 PD4
    #define A1 PD5
    #define A2 PD6
    #define A3 PD7

#endif // ADG726_H