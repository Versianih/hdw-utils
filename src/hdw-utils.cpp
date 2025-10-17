#include "hdw_utils.h"

/* Ports */

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


/* Wait do */

struct WaitDoTask {
  unsigned long startTime;
  unsigned long interval;
  void (*function)();
  bool active;
};

static WaitDoTask* waitDoTasks = nullptr;
static uint8_t waitDoMaxTasks = 0;
static bool waitDoInitialized = false;

void initWaitDo(uint8_t max_wait_do_tasks) {
  if (!waitDoInitialized) {
    waitDoMaxTasks = max_wait_do_tasks;
    waitDoTasks = new WaitDoTask[waitDoMaxTasks];

    for (int i = 0; i < waitDoMaxTasks; i++) {
      waitDoTasks[i].active = false;
    }

    waitDoInitialized = true;
  }
}

void waitDo(unsigned long milis, void (*function)()) {
  if (!waitDoInitialized) return;

  for (int i = 0; i < waitDoMaxTasks; i++) {
    if (waitDoTasks[i].active && waitDoTasks[i].function == function) {
      return;
    }
  }

  for (int i = 0; i < waitDoMaxTasks; i++) {
    if (!waitDoTasks[i].active) {
      waitDoTasks[i].startTime = millis();
      waitDoTasks[i].interval = milis;
      waitDoTasks[i].function = function;
      waitDoTasks[i].active = true;
      return;
    }
  }

  Serial.println("waitDo: Nao ha slots disponiveis para novas tarefas.");
}

void checkWaitDo() {
  if (!waitDoInitialized) return;

  unsigned long currentMillis = millis();
  for (int i = 0; i < waitDoMaxTasks; i++) {
    if (waitDoTasks[i].active) {
      if (currentMillis - waitDoTasks[i].startTime >= waitDoTasks[i].interval) {
        waitDoTasks[i].function();
        waitDoTasks[i].active = false;
      }
    }
  }
}