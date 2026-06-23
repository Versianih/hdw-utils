#include "display.h"

Display<D16x2_I2C>::Display(uint8_t i2c_addr = 0x27)
    : _addr(i2c_addr) {
}