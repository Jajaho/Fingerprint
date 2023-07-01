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

void mux_set_channel(uint8_t channel, uint8_t source){
    adg726_set_channel(channel, source);
}