#include "GeneralAnalogSensor.h"

GeneralAnalogSensor CO2;

void setup()
{
    Serial.begin(9600);
    CO2.setPin(A0,INPUT);
}

void loop()
{
    Serial.println(CO2.getValue());
}
