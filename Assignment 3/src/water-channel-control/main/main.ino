/**
 * ESIOT a.y. 2023/2024 - Assignment 3
 *
 *    .::Smart River Monitoring::.
 *
 *  @authors Javid Ameri, Matilde D'Antino, Federico Diotallevi :3
 *
 */
#include <Arduino.h>
#include "config.h"
#include "devices/WaterValve.h"
#include "devices/Button.h"
#include "devices/LCDDisplay.h"
#include <avr/sleep.h>


// Creazione degli oggetti per ciascun componente hardware
WaterValve waterValve(waterValvePin);
Button button(buttonPin);
LCDDisplay lcdDisplay(lcdRs, lcdEnable, lcdD4, lcdD5, lcdD6, lcdD7);

void setup() {
  // Inizializzazione dei componenti hardware
  waterValve.on();
  button.begin();
  lcdDisplay.initialize();
}

void loop() {
  // Esempio di utilizzo del bottone per controllare la valvola d'acqua
  if (button.wasPressed()) {
    // Accendi la valvola d'acqua
    waterValve.setAngle(90);
    // Mostra un messaggio sul display LCD
    lcdDisplay.print("Valvola accesa", 0, 0);
  }
  if (button.wasReleased()) {
    // Spegni la valvola d'acqua
    waterValve.off();
    // Cancella il messaggio sul display LCD
    lcdDisplay.clear();
  }
}

