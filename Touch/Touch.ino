#include "GeneralDigitalSensor.h"

GeneralDigitalSensor IRDistance;

void setup()
{
    Serial.begin(9600);
    IRDistance.setPin(3,INPUT);
}

void loop()
{
    Serial.println(IRDistance.getValue());
}
