#include "GeneralAnalogSensor.h"

GeneralAnalogSensor flame;

void setup()
{
    Serial.begin(9600);
    flame.setPin(A0,INPUT);
}

void loop()
{
    Serial.println(flame.getValue());
}
