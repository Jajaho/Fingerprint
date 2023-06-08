#include "defines.h"    // Global defines for the project
#include <avr/io.h>     // AVR device-specific IO definitions
#include "adg726.h"

/// @brief Set DDR and PORT for ADG726  
void adg726_init(void){
    // Set pins as output
    SET(DDR, ADG726_NEN);
    SET(DDR, ADG726_NWR);
    SET(DDR, ADG726_NCSA);
    SET(DDR, ADG726_NCSB);
    ASSIGN(DDR, ADG726_A0, 0x0F);

    // Disable adg726 and unselect write mode
    SET(PORT, ADG726_NEN);
    SET(PORT, ADG726_NWR);
    SET(PORT, ADG726_NCSA);
    SET(PORT, ADG726_NCSB);    
}

/// @brief Enable ADG726
void adg726_enable(void){
    CLR(PORT, ADG726_NEN);
}

/// @brief Disable ADG726
void adg726_disable(void){
    SET(PORT, ADG726_NEN);
}

/// @brief Set ADG726 channel of chip A or B
/// @param channel Either 'A', 'B' or 'D' for both channels
/// @param source Source 1 to 12 respectively 
void adg726_set_channel(uint8_t channel, uint8_t source) {
    // Channel selection 
    switch (channel)
    {
    case 'A':   // Channel A
        SET(PORT, ADG726_NCSB);
        CLR(PORT, ADG726_NCSA);
        break;
    case 'B':   // Channel B
        SET(PORT, ADG726_NCSA);
        CLR(PORT, ADG726_NCSB);
        break;
    case 'D':   // Both chips, case falls through to default
    default:
        CLR(PORT, ADG726_NCSA);
        CLR(PORT, ADG726_NCSB);
        break;
    }

    CLR(PORT, ADG726_NWR);  // Enable write mode
    SET(PORT, ADG726_NEN);  // Disable all channels

    // Set logic control bits to select desired source
    ASSIGN(PORT, ADG726_A0, source);    
    // Min. 5ns Address, enable setup time

    // Disable write mode, Input is latched on the rising edge of ADG726_NWR
    SET(PORT, ADG726_NWR);  
    // Min. 2ns Address, enable hold time
    CLR(PORT, ADG726_NEN);  // Enable all channels
    ASSIGN(PORT, ADG726_A0, source);    // Clear control bits
    SET(PORT, ADG726_NCSA);  // Unselect channel A
    SET(PORT, ADG726_NCSB);  // Unselect channel B
}