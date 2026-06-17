#ifndef WAITDO_H
#define WAITDO_H

#include <Arduino.h>


class WaitDo {
    public:
        struct WaitDoTask {
            unsigned long startTime;
            unsigned long interval;
            void (*function)();
            bool active;
        };

        WaitDo(int maxWaitDoTasks = 5);
        int addTask(unsigned long milis, void (*function)());
        void run();

    private:
        int _maxWaitDoTasks;
        WaitDoTask* _waitDoTasks;
}

#endif