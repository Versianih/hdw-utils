#ifndef PIN_H
#define PIN_H

#include <Arduino.h>


#define DIGITAL 0x0
#define ANALOG  0x1

#define INPUT        0x0
#define OUTPUT       0x1
#define INPUT_PULLUP 0x2


class Pin {
    public:
        Pin(uint8_t pin, uint8_t mode_type, uint8_t pin_type = DIGITAL);

        void write(int value = 0);
        int read();
        void toggle();

        void writePwm(uint8_t percent_value = 20);
        int readNormalizer(int readings = 5, int acceptablePercentage = 20, int maxConsecutiveRejections = 3, unsigned long delayMs = 10);

        uint8_t getPin() const;
        uint8_t getModeType() const;
        uint8_t getPinType() const;

    private:
        uint8_t _pin;
        uint8_t _mode_type;
        uint8_t _pin_type;
}

#endif