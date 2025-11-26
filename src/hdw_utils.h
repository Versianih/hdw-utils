#ifndef HDW_UTILS_H
#define HDW_UTILS_H

#include <Arduino.h>

#define DIGITAL 0x0
#define ANALOG 0x1

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

/* Pin */

class Pin {
    public:
        Pin(uint8_t pin, uint8_t mode_type, uint8_t pin_type);

        void write(int value = 0);
        int read();
        void toggle();

        void writePwm(uint8_t percent_value = 20);
        int readNormalizer(int readings = 5, int acceptablePercentage = 20, int maxConsecutiveRejections = 3, unsigned long delayMs = 10);
        void tone(unsigned int frequency, unsigned long duration = 0);
        void noTone();

        uint8_t getPin() const;

    private:
        uint8_t _pin;
        uint8_t _mode_type;
        uint8_t _pin_type;
};


/* Wait do */

class WaitDo {
    public:
        struct WaitDoTask {
            unsigned long startTime;
            unsigned long interval;
            void (*function)();
            bool active;
        };

        WaitDo(int maxWaitDoTasks = 5);
        int addTask(unsigned long milis, void (*function)());
        void run();

    private:
        int _maxWaitDoTasks;
        WaitDoTask* _waitDoTasks;
};

#endif