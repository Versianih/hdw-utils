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
        void writePwm();
        uint8_t getPin() const;

    private:
        uint8_t _pin;
        uint8_t _mode_type;
        uint8_t _port_type;
};


/* Wait do */

void initWaitDo(uint8_t max_wait_do_tasks);
void waitDo(unsigned long milis, void (*function)());
void checkWaitDo();

#endif