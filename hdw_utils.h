#ifndef HDW_UTILS_H
#define HDW_UTILS_H

#include <Arduino.h>

#define DIGITAL 0x0
#define ANALOG 0x1

/* Ports */

class Port {
    public:
        Port(uint8_t pin, uint8_t mode_type, uint8_t port_type);

        void write(int value);
        int read();
        void toggle();
        uint8_t getPin() const;

    private:
        uint8_t _pin;
        uint8_t _mode_type;
        uint8_t _port_type;
};


/* Wait do */

#define MAX_WAIT_DO_TASKS 10

void waitDo(unsigned long milis, void (*function)());
void checkWaitDoTasks(); // void loop();

#endif