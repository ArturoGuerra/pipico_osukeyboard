#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/pio.h>

// Button state machine handler
#include "buttons.pio.h"
#include "buttons.h"


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
 
    tusb_init();

    while(true) {
        tud_task();
        // Handle button states and return current state
        uint32_t button_state = pio_sm_get(pio, sm_buttons);
        // Handle keyboard emulation
        usb_hid_keyboard_handler(button_state);
   }

    return 0;
}



