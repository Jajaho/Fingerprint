/// ADG726 Multiplexer
#ifndef ADG726_H   
#define ADG726_H
    
void adg726_init(void);
void adg726_enable(void);
void adg726_disable(void);
void adg726_set_channel(uint8_t source, uint8_t channel);

#endif // ADG726_H