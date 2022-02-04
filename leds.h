#ifndef _LEDS_H_
#define _LEDS_H_

// To calculate each LED pin subtract the desired LED by the RED LED ex. GREEN_LED - RED_LED
#define RED_LED 16
#define GREEN_LED 17
#define BLUE_LED 18
#define LED_COUNT 3

// short hand mask
#define RED_LED_MASK (1 << 0)
#define GREEN_LED_MASK (1 << 1)
#define BLUE_LED_MASK (1 << 2)

void leds_program_init(PIO pio, uint &sm, uint &offset, uint pin, uint pin_count);

void led_handler(PIO pio, uint sm, uint32_t button_state);

#endif // _LEDS_H_