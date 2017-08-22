#include <Arduino.h>
#include "SoilMoisture.h"

SoilMoisture sm;

void setup()
{
    Serial.begin(9600);
    sm.setPin(A0);
    sm.setAirWaterValue(520,260);
    sm.setup();
}

void loop()
{
    sm.update();
    Serial.println(sm.getValue());
}
