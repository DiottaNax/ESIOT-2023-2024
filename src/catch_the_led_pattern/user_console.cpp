#include "user_console.h"
#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "game_core.h"

#include <EnableInterrupt.h>

#define BOUNCING_TIME 100

// Array containing buttons' pins
uint8_t inputPins[] = {BUT01_PIN, BUT02_PIN, BUT03_PIN, BUT04_PIN};
// Array containing the input pattern formed by player
short inputPattern[] = { NO_SELECTION, NO_SELECTION, NO_SELECTION, NO_SELECTION };

// Number of pressed buttons
short buttonsPressed = 0;
// Boolean variable to check if player pressed button B1
bool playerStartedGame = false;
// Array of boolean to check if each button have already been pressed
bool wasAlreadyPressed[] = {false, false, false, false};
// Array containing the last time each button was pressed
long lastButtonPressedTimeStamps[NUM_INPUT_POS];

void button_handler(int i);
void button_handler_0(){ button_handler(0); }
void button_handler_1(){ button_handler(1); }
void button_handler_2(){ button_handler(2); }
void button_handler_3(){ button_handler(3); }

// Array containing ISR to be attached to buttons
void (*button_handlers[4])() = { button_handler_0, button_handler_1, button_handler_2, button_handler_3 };

void button_handler(int i) {
  long ts = millis();
  if (ts - lastButtonPressedTimeStamps[i] > BOUNCING_TIME) {
    if(!playerStartedGame && i == 0) {
      playerStartedGame = true;
    } else if (game_state == GAME_LOOP_WAITING_PLAYER_PATTERN) {
      lastButtonPressedTimeStamps[i] = ts;
      if (!wasAlreadyPressed[i]) {
        inputPattern[buttonsPressed] = i;
        wasAlreadyPressed[i] = true;
        buttonsPressed++;
        turn_on_led(i);
      }
    }
  }
}

int read_difficulty_level() {
  return map(analogRead(POT_PIN), 0, 1023, 1, DIFFICULTY_LEVELS);
}

short* get_current_pattern() {
  return inputPattern;
}

void init_player_console() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    pinMode(inputPins[i], INPUT);  
    enableInterrupt(inputPins[i], button_handlers[i], CHANGE);       
  }
}

void clear_console() {
  for(int i = 0; i < 100; i++) {
    Serial.println("");
  }
}

void print_on_console(const String& msg) {
  clear_console();
  Serial.println(msg);
}

void reset_player_input(){
  long ts = millis();
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    //Disabling interrupts to prevent concurrency conflicts
    noInterrupts();
    inputPattern[i] = NO_SELECTION;   
    lastButtonPressedTimeStamps[i] = ts;  
    wasAlreadyPressed[i] = false;
    interrupts();
  }
  buttonsPressed = 0;
  delay(BOUNCING_TIME);
}

bool player_input_started(){
  return playerStartedGame;
}

bool all_pressed() {
  for (int i = 0; i < NLEDS; i++) {
    if (wasAlreadyPressed[i] == false) {
      return false;
    }
  }
  return true;
}

