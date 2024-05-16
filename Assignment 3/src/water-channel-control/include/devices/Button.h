#ifndef __BUTTON__
#define __BUTTON__

#include <Arduino.h>

/**
 * @brief Represents a class for interfacing with a button.
 */
class Button {
public:
  /**
   * @brief Constructor for the Button class.
   * @param pin The pin to which the button is connected.
   */
  Button(int pin);

  /**
   * @brief Initializes the button.
   * @details Must be called once at the beginning of the program to set up the button pin as an input.
   */
  void begin();

  /**
   * @brief Checks if the button is currently pressed.
   * @return True if the button is pressed, false otherwise.
   */
  virtual bool isPressed();

  /**
   * @brief Checks if the button was just pressed.
   * @return True if the button was just pressed, false otherwise.
   */
  virtual bool wasPressed();

  /**
   * @brief Checks if the button was just released.
   * @return True if the button was just released, false otherwise.
   */
  virtual bool wasReleased();

private:
  int pin;           /**< The pin to which the button is connected. */
  bool currentState; /**< The current state of the button (pressed or released). */
  bool lastState;    /**< The previous state of the button. */

  virtual void sync();
};

#endif
