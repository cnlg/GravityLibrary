#include "GeneralAnalogSensor.h"

GeneralAnalogSensor sound;

void setup()
{
    Serial.begin(9600);
    sound.setPin(A0,INPUT);
}

void loop()
{
    Serial.println(sound.getValue());
}
