/*
==============================================================================
| This code prints "hello" every 4 seconds while it can perform other tasks. |
==============================================================================
*/

#include "hdw-utils.h"

WaitDo wd(5);

void setup() {
    Serial.begin();
}

void loop() {
    wd.run();

    wd.addTask(4000, printHello);
    
    Serial.println(".");
    
    delay(10);
}

void printHello(){
    Serial.println("Hello");
}