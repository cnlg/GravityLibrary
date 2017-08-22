#include <Arduino.h>
#include "LiquidFlow.h"

LiquidFlow liquidFlow;

void setup()
{
    Serial.begin(9600);
    liquidFlow.setInterrupt(0);
}

void loop()
{
    Serial.println(liquidFlow.getValue());

}
