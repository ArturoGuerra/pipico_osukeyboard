#include <stdio.h>
#include <pico/stdlib.h>
#include <tusb.h>

#include "usb_hid.h"

// has bit mask for button state
#include "buttons.h"

void usb_hid_keyboard_handler(uint32_t buttons) {
    // Return if the keyboard emulator is not ready or if we dont have any buttons pressed
    if (!tud_ready()) return;
    
    // Default payload 
    uint8_t keycodes[6] = {0};
    bool empty = true;
    switch(buttons) {
      case (uint32_t)(LEFT_BUTTON_MASK | RIGHT_BUTTON_MASK): {
        keycodes[0] = KEYBOARD_LEFT; // Left osu key
        keycodes[1] = KEYBOARD_RIGHT; // Right osu key
        empty = false;
        break;
      }
      case (uint32_t)(LEFT_BUTTON_MASK): {
        keycodes[0] = KEYBOARD_LEFT; // Left osu key
        empty = false;
        break;
      }
      case (uint32_t)(RIGHT_BUTTON_MASK): {
        keycodes[0] = KEYBOARD_RIGHT; // Right osu key
        empty = false;
        break;
      }
    }

    // handle setting the keycodes
    if (!empty) {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, keycodes);    
    } else {
        tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL);
    }
    
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
  // TODO not Implemented
  (void) instance;
  (void) report_id;
  (void) report_type;
  (void) buffer;
  (void) reqlen;

  return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
}