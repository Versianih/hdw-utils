#include "hdw_utils.h"

LedRGB::LedRGB(Pin pin_red, Pin pin_green, Pin pin_blue): 
    _pin_red(pin_red), _pin_green(pin_green), _pin_blue(pin_blue){
}


LedRGB::setRGB(uint8_t r, uint8_t g, uint8_t b){
    _pin_red.write(r);
    _pin_green.write(g);
    _pin_blue.write(b);
}

LedRGB::off(){
    _pin_red.write(0);
    _pin_green.write(0);
    _pin_blue.write(0);
}

LedRGB::red(){
    this->setRGB(255, 0, 0);
}

LedRGB::green(){
    this->setRGB(0, 255, 0);
}

LedRGB::blue(){
    this->setRGB(0, 0, 255);
}

LedRGB::yellow(){
    this->setRGB(255, 255, 0);
}

LedRGB::orange(){
    this->setRGB(255, 165, 0);
}

LedRGB::magenta(){
    this->setRGB(255, 0, 255);
}

LedRGB::purple(){
    this->setRGB(128, 0, 128);
}

LedRGB::cyan(){
    this->setRGB(0, 255, 255);
}

LedRGB::white(){
    this->setRGB(255, 255, 255);
}