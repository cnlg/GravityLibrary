#include "GeneralDigitalSensor.h"

GeneralDigitalSensor crash;

void setup()
{
    Serial.begin(9600);
    crash.setPin(3,INPUT);
}

void loop()
{
    Serial.println(crash.getValue());
}
