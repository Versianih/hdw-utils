#ifndef LEDRGB_H
#define LEDRGB_H

#include <Arduino.h>
#include "../pin/pin.h"


class LedRGB {
    public:
        LedRGB(Pin pin_red, Pin pin_green, Pin pin_blue);

        void setRGB(uint8_t r, uint8_t g, uint8_t b);
        void off();

        void red();
        void green();
        void blue();
        void yellow();
        void orange();
        void magenta();
        void purple();
        void cyan();
        void white();

    private:
        Pin _pin_red, _pin_green, _pin_blue;
}

#endif