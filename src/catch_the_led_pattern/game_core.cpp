#include "game_core.h"
#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "user_console.h"
#include <avr/sleep.h>

#define MAX_IDLE_TIME 10000
#define TIME_IN_GAME_OVER 10000

// Array carrying the pattern to be generated
short current_pattern[NLEDS];

// Random time to generate the pattern
long time_to_generate_pattern;

// Time that can be used to input the pattern
long time_to_form_pattern;

// Time to display the pattern
long time_to_display_pattern;

// Difficulty level
int difficulty_level;

// Difficulty scaling factor
double difficulty_scaling_factor = 1;

// The score
long score = 0;

// current game state
int game_state;

// Time in which the game entered in the game state
long entered_state_time;

// How long it the game is in current state
long current_time_in_state;

void change_game_state(int new_state) {
  game_state = new_state;
  entered_state_time = millis();
}

void update_game_state_time() {
  current_time_in_state = millis() - entered_state_time;
}

void check_difficulty_level() {
  int new_difficulty_level = read_difficulty_level();
  if (new_difficulty_level != difficulty_level){
    difficulty_level = new_difficulty_level;
    Serial.println(String("New difficulty Level: ") + difficulty_level);  
  } 
}

void game_intro() {
  print_on_console("Welcome to the Restore the Light Game. Press Key B1 to Start");
  reset_pulsing();
  change_game_state(GAME_WAIT_TO_START);
}

void game_wait_to_start() {
  if (current_time_in_state < MAX_IDLE_TIME){
    go_on_pulsing();
    check_difficulty_level();
    //check if player pressed button B1
    if (player_input_started()){
      change_game_state(GAME_INIT);
    }
  } else {
    change_game_state(GAME_SLEEP);
  }
}

void game_sleep() {
  reset_pulsing();
  delay(500);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();  
  sleep_disable();   
  change_game_state(GAME_INTRO);
}

void game_init(){
  reset_pulsing();
  difficulty_level = read_difficulty_level();
  difficulty_scaling_factor = 1.0 + difficulty_level * 0.1;
  score = 0;
  print_on_console("Go!");
  time_to_display_pattern = T2_TIME;
  time_to_form_pattern = T3_TIME;
  change_game_state(GAME_LOOP_DISPLAY_PATTERN);
}

void fisher_yates_shuffle(short arr[], short n) {
  // Start from the last element and swap one by one
  for (int i = 0; i < n; i++) {
    // Generate a random index between i (inclusive) and n (exclusive)
    int j = random(i, n);
    // Swap arr[i] with arr[j]
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

void generate_pattern() { 
  //Generate pattern by filling and shuffling an array
  for (int i = 0; i < NLEDS; i++){
    current_pattern[i] = i;
  }
  fisher_yates_shuffle(current_pattern, NLEDS);
  change_game_state(GAME_LOOP_DISPLAY_PATTERN);
}

void game_loop_display_pattern() {
  reset_player_input();
  turn_on_leds();
  time_to_generate_pattern = 3000 + random(T1_TIME);
  generate_pattern();
  //turning off each LED one by one, following the random pattern previously generated
  for (int led = 0; led < NLEDS; led++) {
    delay(time_to_display_pattern);
    turn_off_led(current_pattern[led]);
  }
  change_game_state(GAME_LOOP_WAITING_PLAYER_PATTERN);
}

bool check_patterns(short* pattern, short* input){
  for (int i = 0; i < NLEDS; i++){
    if(pattern[i] != input[LAST_POS - i]){
        return false;
    }
  }
  return true;
}

void game_loop_wait_player_pattern() {
  if (current_time_in_state >= time_to_form_pattern || all_pressed()){
      short* input_pattern = get_current_pattern();
      //checking if the player guessed the reversed pattern
      if (!check_patterns(current_pattern, input_pattern)){
        //if not, change state to game over
        change_game_state(GAME_OVER);
      } else {
        //if so, increment score and display a new pattern
        score++;
        time_to_display_pattern /= difficulty_scaling_factor; 
        time_to_form_pattern /= difficulty_scaling_factor;
        print_on_console(String("New Point! Score: ") + score);
        change_game_state(GAME_LOOP_DISPLAY_PATTERN);
      }
  } 
}

void game_over() {
  print_on_console(String("Game Over - Final Score: ") + score);
  led_game_over();
  reset_led_board();
  delay(TIME_IN_GAME_OVER);
  playerStartedGame = false;
  change_game_state(GAME_INTRO);
}
