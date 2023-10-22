/*********
 * 
 * LED BOARD
 * 
 * This module implements the Led Board,
 * containing the 4 leds.
 * 
 */
#ifndef __LED_BOARD__
#define __LED_BOARD__

#include "Arduino.h"

// Initialize the LED board by setting the pin modes
void init_led_board();

// Turn off all LEDs on the board
void reset_led_board();
// Turn off a specific LED
void turn_off_led(short led);
// Turn on all LEDs on the board
void turn_on_leds();
// Turn on a specific LED
void turn_on_led(short led);
// Display a game over animation
void led_game_over();

// Reset the pulsing animation parameters
void reset_pulsing();
// Continuously pulse the LED brightness
void go_on_pulsing();

#endif
