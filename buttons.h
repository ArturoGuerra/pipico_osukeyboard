#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <hardware/pio.h>

#define LEFT_BUTTON 14
#define RIGHT_BUTTON 15
#define LEFT_BUTTON_MASK (1 << 0)
#define RIGHT_BUTTON_MASK (1 << 1)
#define BUTTON_COUNT 2

void buttons_program_init(PIO pio, uint &sm, uint &offset, uint pin, uint pin_count);

uint32_t get_button_state(PIO pio, uint sm);

#endif // _BUTTON_H_