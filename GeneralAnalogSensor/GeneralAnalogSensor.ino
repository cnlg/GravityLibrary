#include "GeneralAnalogSensor.h"

GeneralAnalogSensor LX1972;

void setup()
{
    Serial.begin(9600);
    LX1972.setPin(A0,INPUT);
}

void loop()
{
    Serial.println(LX1972.getValue());
}
