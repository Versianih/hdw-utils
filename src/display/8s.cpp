#include "display.h"


// ==== Display 8s ====

static const uint8_t SEGMENTS[] = {
    0b0111111,  // 0
    0b0000110,  // 1
    0b1011011,  // 2
    0b1001111,  // 3
    0b1100110,  // 4
    0b1101101,  // 5
    0b1111101,  // 6
    0b0000111,  // 7
    0b1111111,  // 8
    0b1101111,  // 9
    0b1110111,  // A
    0b1111100,  // b
    0b0111001,  // C
    0b1011110,  // d
    0b1111001,  // E
    0b1110001,  // F
    0b1000000,  // -
    0b0000000,  // ' '
};


Display<D8s>::Display(Pin a, Pin b, Pin c, Pin d, Pin e, Pin f, Pin g, Pin dp, uint8_t common_type):
    _segments{a, b, c, d, e, f, g, dp}, _common_type(common_type) {
}

void Display<D8s>::_write(uint8_t index, bool on) {
    _segments[index].write(_common_type == COMMON_ANODE ? !on : on);
}

void Display<D8s>::_writeSegments(uint8_t mask) {
    for (uint8_t i = 0; i < 7; i++)
        _write(i, (mask >> i) & 0x1);
}

void Display<D8s>::showDigit(uint8_t digit) {
    if (digit < 0 || digit > 9) return;
    uint8_t mask = SEGMENTS[digit];
    for (uint8_t i = 0; i < 7; i++) {
        _write(i, (mask >> i) & 0x1);
    }
}

void Display<D8s>::showChar(char c) {
    switch (c) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            showDigit(c - '0');
            break;
        case 'A': case 'a': _writeSegments(SEGMENTS[10]); break;
        case 'B': case 'b': _writeSegments(SEGMENTS[11]); break;
        case 'C': case 'c': _writeSegments(SEGMENTS[12]); break;
        case 'D': case 'd': _writeSegments(SEGMENTS[13]); break;
        case 'E': case 'e': _writeSegments(SEGMENTS[14]); break;
        case 'F': case 'f': _writeSegments(SEGMENTS[15]); break;
        case '-':           _writeSegments(SEGMENTS[16]); break;
        case ' ':           _writeSegments(SEGMENTS[17]); break;
        default:            _writeSegments(SEGMENTS[17]); break;
    }
}

void Display<D8s>::showDot(bool on) {
    _segments[7].write(_common_type == COMMON_ANODE ? !on : on);
}

void Display<D8s>::clear() {
    for(uint8_t i = 0; i < 8; i++){
        _segments[i].write(LOW);
    }
}