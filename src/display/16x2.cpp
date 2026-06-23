#include "display.h"

Display<D16x2>::Display(Pin rs, Pin en, Pin d4, Pin d5, Pin d6, Pin d7)
    : _rs(rs), _en(en), _d4(d4), _d5(d5), _d6(d6), _d7(d7),
      _lcd(rs.getPin(), en.getPin(), d4.getPin(), d5.getPin(), d6.getPin(), d7.getPin())
{
    _lcd.begin(16, 2);
}

void Display<D16x2>::print(const char* text) {
    _lcd.print(text);
}

void Display<D16x2>::print(const int text) {
    _lcd.print(text);
}

void Display<D16x2>::print(const float text) {
    _lcd.print(text);
}

void Display<D16x2>::setCursor(uint8_t col, uint8_t row) {
    _lcd.setCursor(col, row);
}

void Display<D16x2>::clear() {
    _lcd.clear();
}