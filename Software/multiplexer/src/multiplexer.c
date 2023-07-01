#include <stdint.h>
#include "adg726.h"
#include "defines.h"

void mux_init(void){
    adg726_init();
}

void mux_enable(void){
    adg726_enable();
}

void mux_disable(void){
    adg726_disable();
}

/// @brief  Select the source connected to the channels of the multiplexer
/// @param channel 
/// @param source Number of the source to connect to the channel, starts at 0
void mux_set_channel(uint8_t channel, uint8_t source){
    adg726_set_channel(channel, source);
}