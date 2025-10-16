#include <hdw_utils.h>

void setup(){
    initWaitDo(5);
}

void loop(){
    checkWaitDoTasks();

    delay(100);
}