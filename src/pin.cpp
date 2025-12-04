#include "hdw_utils.h"

Pin::Pin(
  uint8_t pin,
  uint8_t mode_type,
  uint8_t pin_type
  ): _pin(pin), _mode_type(mode_type), _pin_type(pin_type) {

  pinMode(_pin, _mode_type);
}

void Pin::write(int value) {
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

void Pin::pwm(float percent, uint16_t frequency) {
    if (_mode_type != OUTPUT && _pin_type != DIGITAL) return;
    
    percent = constrain(percent, 0.0, 100.0);
    
    #ifdef ESP32
        uint8_t channel = _pin % 16;
        uint16_t dutyCycle = (uint16_t)((percent / 100.0) * 255.0);
        
        ledcSetup(channel, frequency, 8);
        ledcAttachPin(_pin, channel);
        ledcWrite(channel, dutyCycle);
    #else
        uint8_t pwmValue = (uint8_t)((percent / 100.0) * 255.0);
        analogWrite(_pin, pwmValue);
    #endif
}

void Pin::pwmStop() {
    #ifdef ESP32
        uint8_t channel = _pin % 16;
        ledcDetachPin(_pin);
    #else
        analogWrite(_pin, 0);
    #endif
}

uint8_t Pin::getPin() const {
  return _pin;
}

int Pin::readNormalizer(int readings, int acceptablePercentage, int maxConsecutiveRejections, unsigned long delayMs) {
  if (readings == 0 || _pin_type != ANALOG) return 0;
  acceptablePercentage = constrain(acceptablePercentage, 5, 100);
  maxConsecutiveRejections = constrain(maxConsecutiveRejections, 2, 10);
  
  int validReadings = 0, sumReading = 0, lastReading = 0;
  int consecutiveRejections = 0;
  int lastRejectedReading = 0;
  
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
      consecutiveRejections = 0;
    } else {
      if (consecutiveRejections > 0 && abs(reading - lastRejectedReading) <= (reading * acceptablePercentage) / 100) {
        consecutiveRejections++;
      } else {
        consecutiveRejections = 1;
        lastRejectedReading = reading;
      }
      
      if (consecutiveRejections >= maxConsecutiveRejections) {
        sumReading += reading;
        validReadings++;
        lastReading = reading;
        consecutiveRejections = 0;
      }
    }
    
    delay(delayMs);
  }
  
  return sumReading / readings;
}

void Pin::tone(unsigned int frequency, unsigned long duration) {
  if (_pin_type != DIGITAL || _mode_type != OUTPUT) return;
  if (duration == 0) {
    ::tone(_pin, frequency);
  } else {
    ::tone(_pin, frequency, duration);
  }
}

void Pin::noTone() {
  if (_pin_type != DIGITAL || _mode_type != OUTPUT) return;
  ::noTone(_pin);
}