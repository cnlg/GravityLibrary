#include "GeneralDigitalSensor.h"

GeneralDigitalSensor touch;

void setup()
{
    Serial.begin(9600);
    touch.setPin(3,INPUT);
}

void loop()
{
    Serial.println(touch.getValue());
}
