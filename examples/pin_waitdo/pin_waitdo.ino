#include <hdw_utils.h>

Pin LED(2, OUTPUT, DIGITAL);
WaitDo wd(5);

void setup(){
    Serial.begin(9600);
}

void loop(){
    wd.run()

    wd.addTask(3000, toggleLed);

    delay(10);
}

void toggleLed(){
    LED.toggle();
    Serial.println("LED TOGGLE");
}