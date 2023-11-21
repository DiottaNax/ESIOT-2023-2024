#include "LCDDisplay.h"

LCDDisplay::LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7) : lcd(rs, enable, d4, d5, d6, d7) {}

  void LCDDisplay::initialize() {
      lcd.begin(16, 2);
  }

  void LCDDisplay::clear() {
      lcd.clear();
  }
  void LCDDisplay::print(String text, int column, int row) {
      setCursor(column, row);
      lcd.print(text);
  }

  void LCDDisplay::setCursor(int column, int row) {
      lcd.setCursor(column, row);
  }