#include "hdw_utils.h"

Buzzer::Buzzer(Pin pin): _pin(pin) {}

void Buzzer::tone(unsigned int frequency, unsigned long duration) {
  if (_pin_type != DIGITAL || _mode_type != OUTPUT) return;
  if (duration == 0) {
    ::tone(_pin, frequency);
  } else {
    ::tone(_pin, frequency, duration);
  }
}

void Buzzer::noTone() {
  if (_pin_type != DIGITAL || _mode_type != OUTPUT) return;
  ::noTone(_pin);
}