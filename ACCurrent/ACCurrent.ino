#include <Arduino.h>
#include "ACCurrent_S.h"

ACCurrent_S acccurrent;

void setup()
{
   acccurrent.setPin(A2);
   acccurrent.setup();

}

void loop()
{
    acccurrent.update();
    acccurrent.getValue();
    
}
