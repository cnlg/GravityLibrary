#include <Arduino.h>
#include "ACCurrent_S.h"

ACCurrent_S acccurrent;



void handleExceed(float maxAccValue)
{
    Serial.println(maxAccValue);
}

void setup()
{
   acccurrent.setPin(A2);
   acccurrent.setup();
   acccurrent.setHandleExceed(handleExceed, 10);

}

void loop()
{
    acccurrent.update();
    acccurrent.getValue();
    
}
