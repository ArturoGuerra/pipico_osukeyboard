#ifndef _USB_HID_
#define _USB_HID_

#include <stdio.h>

#define KEYBOARD_LEFT  HID_KEY_A
#define KEYBOARD_RIGHT HID_KEY_S

/* Status LED Blink Pattern
250 ms : Device not mounted
1000 ms : Device mounted
25000 ms : Device suspended
*/
enum {
    BLINK_NOT_MOUNTED = 250,
    BLINK_MOUNTED = 1000,
    BLINK_SUSPENDED = 2500,
};

enum
{
  REPORT_ID_KEYBOARD = 1,
  REPORT_ID_MOUSE,
  REPORT_ID_CONSUMER_CONTROL,
  REPORT_ID_GAMEPAD,
  REPORT_ID_COUNT
};

// Key codes will be embedded in the uint32_t param
void usb_hid_keyboard_handler(uint32_t buttons);

uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen);

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize);

#endif // _USB_HID_
