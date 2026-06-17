#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "../pin/pin.h"

#define D16x2     0x0
#define D16x2_I2C 0x1
#define D8s       0x2

#define COMMON_ANODE   0x0
#define COMMON_CATHODE 0x1


template<uint8_t T>
class Display;


template<>
class Display<D16x2> {
public:
    Display(Pin rs, Pin en, Pin d4, Pin d5, Pin d6, Pin d7);

    void print(const char* text);
    void setCursor(uint8_t col, uint8_t row);
    void clear();

private:
    Pin _rs, _en, _d4, _d5, _d6, _d7;
};


template<>
class Display<D16x2_I2C> {
public:
    Display(uint8_t i2c_addr = 0x27);

    void print(const char* text);
    void setCursor(uint8_t col, uint8_t row);
    void clear();
    void setBacklight(bool on);

private:
    uint8_t _addr;
};


template<>
class Display<D8s> {
    public:
        Display(Pin a, Pin b, Pin c, Pin d, Pin e, Pin f, Pin g, Pin dp, uint8_t common_type = COMMON_ANODE);

        void showDigit(uint8_t digit);
        void showChar(char c);
        void showDot(bool on = true);
        void clear();

    private:
        Pin _segments[8];
        bool _common_type;

        void _write(uint8_t index, bool on);
        void _writeSegments(uint8_t mask);
};

#endif