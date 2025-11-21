#include "hdw_utils.h"

Pin::Pin(
  uint8_t pin,
  uint8_t mode_type,
  uint8_t pin_type
  ): _pin(pin), _mode_type(mode_type), _pin_type(pin_type) {

  pinMode(_pin, _mode_type);
}

void Pin::write(int value = 0) {
  if (_mode_type == OUTPUT) {
    if (_pin_type == DIGITAL) {
      digitalWrite(_pin, value);
    } else if (_pin_type == ANALOG) {
      analogWrite(_pin, value);
    }
  }
}

int Pin::read() {
  if (_mode_type == INPUT || _mode_type == INPUT_PULLUP) {
    if (_pin_type == DIGITAL) {
      return digitalRead(_pin);
    } else if (_pin_type == ANALOG) {
      return analogRead(_pin);
    }
  }
  return -1;
}

void Pin::toggle() {
  if (_mode_type == OUTPUT && _pin_type == DIGITAL) {
    digitalWrite(_pin, !digitalRead(_pin));
  }
}

void Pin::writePwm(uint8_t percent_value = 0) {
  if (_mode_type == OUTPUT) { 
    if (percent_value > 100) percent_value = 100;
    uint8_t pwm_value = (percent_value * 255) / 100;
    analogWrite(_pin, pwm_value);
  }
}

uint8_t Pin::getPin() const {
  return _pin;
}

int Pin::readNormalizer(int readings = 5, int acceptablePercentage = 20, unsigned long delayMs = 10) {
  if (readings == 0 || _pin_type != ANALOG) return 0;
  acceptablePercentage = constrain(acceptablePercentage, 5, 100);
  
  int validReadings = 0, sumReading = 0, lastReading = 0;
  
  lastReading = this->read();
  delay(delayMs);

  while (validReadings < readings) {
    int reading = this->read();
    
    int difference = abs(reading - lastReading);
    int maxDifference = (lastReading * acceptablePercentage) / 100;
    
    if (difference <= maxDifference) {
      sumReading += reading;
      validReadings++;
      lastReading = reading;
    }
    
    delay(delayMs);
  }
  
  return sumReading / readings;
}

void Pin::tone(unsigned int frequency, unsigned long duration = 0) {
  if (duration == 0) {
    ::tone(_pin, frequency);
  } else {
    ::tone(_pin, frequency, duration);
  }
}

void Pin::noTone() {
  ::noTone(_pin);
}