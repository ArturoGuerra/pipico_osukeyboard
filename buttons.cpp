#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/pio.h>
#include "buttons.h"
#include "buttons.pio.h"

void buttons_program_init(PIO pio, uint &sm, uint &offset, uint pin, uint pin_count) {
    offset = pio_add_program(pio, &buttons_program);
    sm = pio_claim_unused_sm(pio, true);

    for (uint i = 0; i < pin_count; i++) {
        pio_gpio_init(pio, pin + i); // Sets pin to output 
        gpio_pull_down(pin + i); // Sets input pins to a default low 
    }
    
    pio_sm_set_consecutive_pindirs(pio, sm, pin, pin_count, false);
    
    pio_sm_config c = buttons_program_get_default_config(offset); 
    
    sm_config_set_in_pins(&c, pin);
    sm_config_set_in_shift(&c, false, true, 2);

    sm_config_set_clkdiv(&c, 1); 

    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_RX);

    pio_sm_init(pio, sm, offset, &c);
}