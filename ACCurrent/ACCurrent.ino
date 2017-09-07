#include <Arduino.h>
#include "ACCurrent_S.h"

ACCurrent_S acccurrent;
float accValue = 0;

void setup()
{
   acccurrent.setPin(A2);
   acccurrent.setup();
}

void loop()
{
    acccurrent.update();
    accValue = acccurrent.getValue();
    
}
