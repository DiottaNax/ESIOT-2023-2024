#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class LCDDisplay {
public:
  LCDDisplay(int rs, int enable, int d4, int d5, int d6, int d7);

  void initialize();
  void clear();
  void print(String text, int column, int row);
  void setCursor(int column, int row);

private:
  LiquidCrystal lcd;
};

#endif
