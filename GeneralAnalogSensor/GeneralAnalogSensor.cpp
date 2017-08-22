#include <Arduino.h>
#include "GeneralAnalogSensor.h"

GeneralAnalogSensor::GeneralAnalogSensor()
{

}

GeneralAnalogSensor::~GeneralAnalogSensor()
{

}

void GeneralAnalogSensor::setPin(uint8_t pin, uint8_t mode)
{
    this->_pin = pin;
    pinMode(pin,mode);
}

int GeneralAnalogSensor::getValue()
{
    return analogRead(this->_pin);
}

void GeneralAnalogSensor::setValue(int value)
{
    analogWrite(this->_pin,value);
}
