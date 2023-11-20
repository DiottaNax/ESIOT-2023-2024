#include "Arduino.h"
#include "config.h"
#include "game_core.h"

// Define an array of LED pin numbers
uint8_t ledPin[] = {LED01_PIN, LED02_PIN, LED03_PIN, LED04_PIN};
// Current intensity for the Start LED pulsing
uint8_t pulseIntensity = 0;
// Fade amount to let the led pulsing
uint8_t pulseDelta = 5;

void init_led_board() {   
  for (int i = 0; i < NLEDS; i++){
    pinMode(ledPin[i], OUTPUT);     
  }
  pinMode(LED_START, OUTPUT);   

}

void reset_led_board() {
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], LOW);     
  }
}

void reset_pulsing() {
  pulseIntensity = 0;
  pulseDelta = 5;
  analogWrite(LED_START, pulseIntensity);   
}

void go_on_pulsing(){
  analogWrite(LED_START, pulseIntensity);   
  pulseIntensity = pulseIntensity + pulseDelta;
  if (pulseIntensity == 0 || pulseIntensity == 255) {
    pulseDelta = -pulseDelta ; 
  }     
  delay(15);                               
}

void turn_on_leds(){
  for (int i = 0; i < NLEDS; i++){
    digitalWrite(ledPin[i], HIGH);
  }
}

void turn_on_led(short led){
  digitalWrite(ledPin[led], HIGH);
}

void turn_off_led(short led){
  digitalWrite(ledPin[led], LOW);
}

void led_game_over() {
  digitalWrite(LED_START,HIGH);
  delay(1000);
  digitalWrite(LED_START,LOW);
}

