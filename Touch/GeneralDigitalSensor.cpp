#include <Arduino.h>
#include "GeneralDigitalSensor.h"

GeneralDigitalSensor::GeneralDigitalSensor()
{

}

GeneralDigitalSensor::~GeneralDigitalSensor()
{

}

void GeneralDigitalSensor::setPin(uint8_t pin, uint8_t mode)
{
    this->_pin = pin;
    pinMode(pin,mode);
}

uint8_t GeneralDigitalSensor::getValue()
{
    return digitalRead(this->_pin);
}

void GeneralDigitalSensor::setValue(uint8_t value)
{
    digitalWrite(this->_pin,value);
}
