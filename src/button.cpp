#include "hdw_utils.h"

Button::Button(Pin pin, bool debouncing): _pin(pin), _debouncing(debouncing){
    switch (_pin.getModeType())
    {
    case INPUT:
        _logicalLevel = 1;
        break;

    case INPUT_PULLUP:
        _logicalLevel = 0;
        break;

    default:
        _logicalLevel = 1;
        break;
    }
}

bool Button::isPressed() {

    return false;
}