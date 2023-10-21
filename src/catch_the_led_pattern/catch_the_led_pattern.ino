/*
 * ESIOT a.y. 2023/2024
 *
 * ASSIGNMENT #1 - CATCH THE LED PATTERN  
 * 
 * Authors: Ameri Javid, D'Antino Matilde, Diotallevi Federico :3
 * 
 */
#include "config.h"
#include "stdio.h"
#include "game_core.h"
#include "user_console.h" 
#include "led_board.h"

void setup() {
  init_player_console();
  init_led_board();
  //test_led_board();
  Serial.println("Setup finished");
  change_game_state(GAME_INTRO);
}

void loop(){ 
  update_game_state_time();
 
  switch (game_state) { 
  case GAME_INTRO:
    //Serial.println("Entered Game Intro");
    game_intro();
    break;
  case GAME_WAIT_TO_START:
    //Serial.println("Entered Game Wait to Start");
    game_wait_to_start();
    break;
  case GAME_INIT:
    //Serial.println("Entered Game Init");
    game_init();
    break;
  case GAME_LOOP_DISPLAY_PATTERN:
    game_loop_display_pattern();
    break;
  case GAME_LOOP_WAITING_PLAYER_PATTERN:
    game_loop_wait_player_pattern();
    break;
  case GAME_OVER:
    game_over();
    break;
  case GAME_SLEEP:
    Serial.println("SLEEPING...");
    game_sleep();
    break;
  }
}
