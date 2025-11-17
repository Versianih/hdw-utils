#include "hdw_utils.h"

WaitDo::WaitDo(int maxWaitDoTasks): _maxWaitDoTasks(maxWaitDoTasks) {
  _waitDoTasks = new WaitDoTask[maxWaitDoTasks];

  for (int i = 0; i < _maxWaitDoTasks; i++) {
    _waitDoTasks[i].active = false;
  }
}

int WaitDo::addTask(unsigned long milis, void (*function)()){
  for (int i = 0; i < _maxWaitDoTasks; i++) {
    if (_waitDoTasks[i].active && _waitDoTasks[i].function == function) {
      return 0;
    }

    if (!_waitDoTasks[i].active) {
      _waitDoTasks[i].startTime = millis();
      _waitDoTasks[i].interval = milis;
      _waitDoTasks[i].function = function;
      _waitDoTasks[i].active = true;
      return 0;
    }
  }

  return 1; 
}

void WaitDo::run(){
  unsigned long currentTime = millis();
  for (int i = 0; i < _maxWaitDoTasks; i++) {
    if (_waitDoTasks[i].active) {
      if (currentTime - _waitDoTasks[i].startTime >= _waitDoTasks[i].interval) {
        _waitDoTasks[i].function();
        _waitDoTasks[i].active = false;
      }
    }
  }
}