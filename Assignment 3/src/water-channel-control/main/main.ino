/**
 * ESIOT a.y. 2023/2024 - Assignment 3
 *
 *    .::Smart River Monitoring::.
 *
 *  @authors Javid Ameri, Matilde D'Antino, Federico Diotallevi :3
 *
 */
#include <Arduino.h>
#include <avr/sleep.h>

void setup() {
  
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

