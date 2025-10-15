#include "hdw_utils.h"

/* Ports */

Port::Port(
    uint8_t pin,
    uint8_t mode_type,
    uint8_t port_type
    ): _pin(pin), _mode_type(mode_type), _port_type(port_type) {

    pinMode(_pin, _mode_type);
}

void Port::write(int value) {
    if (_mode_type == OUTPUT) {
        if (_port_type == DIGITAL) {
            digitalWrite(_pin, value);
        } else if (_port_type == ANALOG) {
            analogWrite(_pin, value);
        }
    }
}

int Port::read() {
    if (_mode_type == INPUT || _mode_type == INPUT_PULLUP) {
        if (_port_type == DIGITAL) {
            return digitalRead(_pin);
        } else if (_port_type == ANALOG) {
            return analogRead(_pin);
        }
    }
    return -1;
}

void Port::toggle() {
    if (_mode_type == OUTPUT && _port_type == DIGITAL) {
        digitalWrite(_pin, !digitalRead(_pin));
    }
}

uint8_t Port::getPin() const {
    return _pin;
}


/* Wait do */

struct WaitDoTask {
  unsigned long startTime;
  unsigned long interval;
  void (*function)();
  bool active;
};

WaitDoTask waitDoTasks[MAX_WAIT_DO_TASKS];

static bool waitDoInitialized = false;

static void initWaitDoTasks() {
  if (!waitDoInitialized) {
    for (int i = 0; i < MAX_WAIT_DO_TASKS; i++) {
      waitDoTasks[i].active = false;
    }
    waitDoInitialized = true;
  }
}

void waitDo(unsigned long milis, void (*function)()) {
  initWaitDoTasks();

  for (int i = 0; i < MAX_WAIT_DO_TASKS; i++) {
    if (waitDoTasks[i].active && waitDoTasks[i].function == function) {
      return;
    }
  }

  for (int i = 0; i < MAX_WAIT_DO_TASKS; i++) {
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

void checkWaitDoTasks() {
  initWaitDoTasks();

  unsigned long currentMillis = millis();
  for (int i = 0; i < MAX_WAIT_DO_TASKS; i++) {
    if (waitDoTasks[i].active) {
      if (currentMillis - waitDoTasks[i].startTime >= waitDoTasks[i].interval) {
        
        waitDoTasks[i].function();
        waitDoTasks[i].active = false;
      }
    }
  }
}