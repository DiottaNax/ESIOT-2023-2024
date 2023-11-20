/*********
 * 
 * USER CONSOLE
 * 
 * This module implements the user console,
 * containing the buttons for interacting
 * with the user as well as the console
 * to output the messages.
 * 
 */
#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__
#include "Arduino.h" 

#define NUM_INPUT_POS 4
#define LAST_POS 3

#define NO_SELECTION -1
#define DIFFICULTY_LEVELS 4

// Button press handler
void button_handler(int button);

// Initialize the player's console
void init_player_console();

// Clears the serial monitor
void clear_console();

// Print a message on the serial console
void print_on_console(const String& msg);

// Read the difficulty level
int read_difficulty_level();

// Check if the player has started the game
bool player_input_started();

// Reset the player's input, including button presses
void reset_player_input();

// Get current pattern inserted by player
short* get_current_pattern();

// Check if all buttons have been pressed
bool all_pressed();


#endif
