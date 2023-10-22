#ifndef __GAME_CORE__
#define __GAME_CORE__

#include "Arduino.h"

#define GAME_INTRO 1
#define GAME_WAIT_TO_START 2
#define GAME_INIT 3
#define GAME_LOOP_GENERATE_PATTERN 4
#define GAME_LOOP_DISPLAY_PATTERN 5
#define GAME_LOOP_WAITING_PLAYER_PATTERN 6
#define GAME_OVER 7
#define GAME_SLEEP 8

#define T1_TIME 1000
#define T2_TIME 2000
#define T3_TIME 5000

extern int game_state;
extern bool playerStartedGame;

// Function to update the time spent in the current game state 
void update_game_state_time();

// Function to change the game state and record the time it entered the state 
void change_game_state(int new_state);

/*Function to transition to the game over state*/
void change_to_game_over();

// Function to check and update the difficulty level based on user input 
void check_difficulty_level();

// Function to shuffle the elements in an array using Fisher-Yates shuffle
void fisherYatesShuffle(short arr[], short n);

// Function to generate a pattern for the game
void generate_pattern();

// Function to check if two patterns match by comparing if the first pattern is the reverse of the other
bool check_patterns(short* pattern, short* input);

// Behaviour in the specific game states:
// Function for the game's introduction
void game_intro();
// Function for waiting for the player to start the game
void game_wait_to_start();
// Function to initialize the game
void game_init();
// Function for displaying the pattern
void game_loop_display_pattern();
//Function for waiting for the player to input a pattern and checking if it matches
void game_loop_wait_player_pattern();
// Function for handling the game over state
void game_over();
// Function to put the Arduino into a low-power sleep mode
void game_sleep();

#endif
