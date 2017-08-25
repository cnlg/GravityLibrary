#include "GeneralDigitalSensor.h"

int pirPin = 2;
int ledPin = 13;

GeneralDigitalSensor pir;
GeneralDigitalSensor led; 

void ledOn(uint8_t value)
{
    led.setValue(HIGH);
}

void ledOff(uint8_t value)
{
    led.setValue(LOW);
}

void setup()
{
    pir.setPin(pirPin,INPUT);
    led.setPin(ledPin,OUTPUT);
    pir.setHandleM(ledOn, 1);
    pir.setHandleL(ledOff,0); 
}

void loop()
{
    pir.update();
}
