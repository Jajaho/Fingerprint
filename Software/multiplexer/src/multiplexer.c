#include <stdint.h>
#include "adg726.h"
#include "defines.h"

void mux_init(void){
    adg726_init();
}

void mux_set_channel(uint8_t source, uint8_t channel){
    adg726_set_channel(source, channel);
}