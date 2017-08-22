#include <Arduino.h>
#include "LiquidFlow.h"

double waterFlow = 0;

LiquidFlow::LiquidFlow()
{

}

LiquidFlow::~LiquidFlow()
{

}

void pulse()
{
    waterFlow += 1.0 / 450.0;
}

void LiquidFlow::setInterrupt(uint8_t interruptNum)
{
    attachInterrupt(interruptNum, pulse, RISING);  //DIGITAL Pin 2: Interrupt 0
}

double LiquidFlow::getValue()
{
    return waterFlow;
}
