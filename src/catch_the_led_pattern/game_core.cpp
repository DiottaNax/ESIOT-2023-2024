#include "game_core.h"
#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "user_console.h"
#include <avr/sleep.h>

#define MAX_IDLE_TIME 10000
#define TIME_IN_GAME_OVER 1000

/* current pattern to be generated */
short current_pattern[NLEDS];

/* current max time to generate the pattern (random) */
long max_time_to_generate_pattern;

/* current max time that can be used to input the pattern */
long max_time_to_form_pattern;

/* current max time to display the pattern */
long max_time_to_display_pattern;

/* difficulty level */
int difficulty_level;

/* difficulty scaling factor */
double difficulty_scaling_factor = 1;

/* the score */
long score = 0;

/* current game state */
int game_state;

/* time in which the game entered in the game state */
long entered_state_time;

/* how long it the game is in current state */
long current_time_in_state;


/* =========== procedures about game state ======== */

void change_game_state(int new_state){
  game_state = new_state;
  entered_state_time = millis();
}

void update_game_state_time(){
  current_time_in_state = millis() - entered_state_time;
}

void check_difficulty_level(){
  int new_difficulty_level = read_difficulty_level();
  if (new_difficulty_level != difficulty_level){
    difficulty_level = new_difficulty_level;
    print_on_console(String("New difficulty Level: ") + difficulty_level);  
  } 
}

void game_intro(){
  //reset_led_board();   
  print_on_console("Welcome to the Restore the Light Game. Press Key T1 to Start");
  reset_pulsing();
  change_game_state(GAME_WAIT_TO_START);
}

void game_wait_to_start(){
  if (current_time_in_state < MAX_IDLE_TIME){
    go_on_pulsing();
    check_difficulty_level();
    if (player_input_started()){
      change_game_state(GAME_INIT);
    }
  } else {
    change_game_state(GAME_SLEEP);
  }
}

void game_sleep(){
  log("Going to sleep..");
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
  difficulty_scaling_factor = 1.0 + difficulty_level*0.1;
  /*log(String("Scaling F: ") + difficulty_scaling_factor);*/
  
  score = 0;
  
  print_on_console("Go!");  
  max_time_to_display_pattern = T2_TIME; 
  max_time_to_form_pattern = T3_TIME;
  change_game_state(GAME_LOOP_DISPLAY_PATTERN);
}

void fisherYatesShuffle(short arr[], short n) {
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

void generate_pattern(){ 
  /* generate pattern */
  for (int i = 0; i < NLEDS; i++){
    current_pattern[i] = i;
  }
  fisherYatesShuffle(current_pattern, NLEDS);
  change_game_state(GAME_LOOP_DISPLAY_PATTERN);
}

void game_loop_display_pattern(){
  reset_player_input();
  turn_on_leds();
  max_time_to_generate_pattern = 3000 + random(T1_TIME);
  generate_pattern();
  delay(max_time_to_generate_pattern);
  //log(String("Now it's input time... waiting for: ") + max_time_to_form_pattern);
  for (int led = 0; led < NLEDS; led++) {
    turn_off_led(current_pattern[led]); 
    if (led < NLEDS-1) {
      delay(max_time_to_form_pattern);
    }
  }
  change_game_state(GAME_LOOP_WAITING_PLAYER_PATTERN);
}

void change_to_game_over(){
  print_on_console(String("Game Over - Final Score: ") + score);
  led_game_over();
  reset_led_board();
  delay(10000);
  change_game_state(GAME_OVER);
}

bool check_patterns(short* pattern, short* input){
  for (int i = 0; i < NLEDS; i++){
    if(pattern[i] != input[NLEDS - 1 - i]){
        return false;
    }
  }
  return true;
}

void game_loop_wait_player_pattern(){
  if (current_time_in_state >= max_time_to_form_pattern /*|| allPressed()*/){
      short* input_pattern = get_current_pattern();  
      if (!check_patterns(current_pattern, input_pattern)){
        change_to_game_over();
      } else {
        score++;
        max_time_to_display_pattern /= difficulty_scaling_factor; 
        max_time_to_form_pattern /= difficulty_scaling_factor;
        print_on_console(String("New Point! Score: ") + score);
        change_game_state(GAME_LOOP_DISPLAY_PATTERN);
      }
  } 
}

void game_over(){
  if (current_time_in_state > TIME_IN_GAME_OVER){
    playerStartedGame = false;
    change_game_state(GAME_INTRO);
  }
}
