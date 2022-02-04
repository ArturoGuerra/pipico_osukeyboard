#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/pio.h>

// Button state machine handler
#include "buttons.pio.h"
#include "buttons.h"

// LED state machine handler
#include "leds.pio.h"
#include "leds.h"

// Handles keyboard emulation
#include <tusb.h>
#include "usb_hid.h"

 

int main() {
    stdio_init_all();

    // Initialize the PIO controller 
    const PIO pio = pio0;

    uint buttons_offset, sm_buttons;
    buttons_program_init(pio, sm_buttons, buttons_offset, LEFT_BUTTON, BUTTON_COUNT);
    pio_sm_set_enabled(pio, sm_buttons, true);

    uint leds_offset, sm_leds;
    leds_program_init(pio, sm_leds, leds_offset, RED_LED, 3);
    pio_sm_set_enabled(pio, sm_leds, true);
    
    // Turn on ALL LEDs
    pio_sm_put(pio, sm_leds, (uint32_t)(RED_LED_MASK | GREEN_LED_MASK | BLUE_LED_MASK));
    
    tusb_init();

    while(true) {
        tud_task();
        // Handle button states and return current state
        uint32_t button_state = get_button_state(pio, sm_buttons);
        // Handle LED state, should probably happen on a different core
        led_handler(pio, sm_leds, button_state);
        // Handle keyboard emulation
        usb_hid_keyboard_handler(button_state);
   }

    return 0;
}



