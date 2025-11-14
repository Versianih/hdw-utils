#include <hdw_utils.h>

Pin LED1(18, OUTPUT, DIGITAL);
Pin BUTTON(17, INPUT_PULLUP, DIGITAL);

void setup(){
    Serial.begin(9600);
}

void loop(){
    if (BUTTON.read() == 0){
        LED1.write(HIGH);
        Serial.print("LED");
    }
    LED1.write(LOW);
    delay(100);
}