#include "GeneralDigitalSensor.h"

GeneralDigitalSensor relay;

void setup()
{
    relay.setPin(3,OUTPUT);
}

void loop()
{
    relay.setValue(HIGH);
    delay(2000);
    relay.setValue(LOW);
    delay(2000);
}
