#ifndef _MULTIPLEXER_H_
#define _MULTIPLEXER_H_

void mux_init(void);
void mux_enable(void);
void mux_disable(void);
void mux_set_channel(uint8_t source, uint8_t channel);

#endif // _MULTIPLEXER_H_