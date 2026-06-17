#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "../pin/pin.h"


class Buzzer {
    public:
        Buzzer(Pin pin);
        void tone(unsigned int frequency, unsigned long duration = 0);
        void noTone();
        
    private:
        Pin _pin;
}

#endif