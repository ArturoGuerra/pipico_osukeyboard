#include <stdio.h>
#include <hardware/pio.h>

#include "buttons.h"

#include "leds.h"
#include "leds.pio.h"

// Includes bit mask for button state

void leds_program_init(PIO pio, uint &sm, uint &offset, uint pin, uint pin_count) {
    offset = pio_add_program(pio, &leds_program);
    sm = pio_claim_unused_sm(pio, true);
    
    for (uint i = 0; i < pin_count; i++) pio_gpio_init(pio, pin + i); // Sets pin to output 
    
    pio_sm_config c = leds_program_get_default_config(offset);
    
    pio_sm_set_consecutive_pindirs(pio, sm, pin, pin_count, true); // Sets consecutive pins to output

    sm_config_set_out_pins(&c, pin, pin_count); // Sets output pins
   
    sm_config_set_fifo_join(&c, PIO_FIFO_JOIN_TX);

    pio_sm_init(pio, sm, offset, &c);
}

// Fetches current state value from state machine
void led_handler(PIO pio, uint sm, uint32_t button_state) {
    switch(button_state) {
    case (uint32_t)(LEFT_BUTTON_MASK | RIGHT_BUTTON_MASK):
        pio_sm_put(pio, sm, (uint32_t)BLUE_LED_MASK);
        printf("BLUE LED\n");
        break;
    case (uint32_t)RIGHT_BUTTON_MASK:
        pio_sm_put(pio, sm, (uint32_t)GREEN_LED_MASK);
        printf("GREEN LED\n");
        break;
    case (uint32_t)LEFT_BUTTON_MASK:
        pio_sm_put(pio, sm, (uint32_t)RED_LED_MASK);
        printf("RED LED\n");
        break;
    default:
        pio_sm_put(pio, sm, (uint32_t)(RED_LED_MASK | GREEN_LED_MASK | BLUE_LED_MASK));
        printf("ALL LEDs\n");
        break;
    }
}