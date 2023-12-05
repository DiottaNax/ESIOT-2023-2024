#ifndef __DISPLAY__
#define __DISPLAY__

#include <Arduino.h>
#include <LiquidCrystal.h>

/**
 * @brief Represents a class for interfacing with an LCD display using the LiquidCrystal library.
 */
class LCDDisplay {
public:
  /**
   * @brief Constructor for the LCDDisplay class.
   * 
   * @param rs Pin connected to the RS (Register Select) pin of the LCD.
   * @param enable Pin connected to the Enable pin of the LCD.
   * @param d4-d7 Pins connected to the D4-D7 data pins of the LCD.
   */
  LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7);

  /**
   * @brief Initializes the LCD display.
   */
  void initialize();

  /**
   * @brief Clears the content of the LCD display.
   */
  void clear();

  /**
   * @brief Prints a string to the LCD display at a specified position.
   * 
   * @param text The text to be printed.
   * @param column The column position where the text should be printed.
   * @param row The row position where the text should be printed.
   */
  void print(String text, int column, int row);

  /**
   * @brief Sets the cursor position on the LCD display.
   * 
   * @param column The column position where the cursor should be set.
   * @param row The row position where the cursor should be set.
   */
  void setCursor(int column, int row);

  /**
   * @brief Scrolls the contents of the LCD display to the left.
   */
  void scrollToLeft();

private:
  LiquidCrystal lcd; /**< The LiquidCrystal object used for interfacing with the LCD display. */
};

#endif
