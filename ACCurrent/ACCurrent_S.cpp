#include "ACCurrent_S.h"
#include "Arduino.h"

ACCurrent_S::ACCurrent_S():vref(0)
{
}

ACCurrent_S::~ACCurrent_S()
{
}
    
void ACCurrent_S::setPin(int pin)
{
    acPin = pin;
}

void ACCurrent_S::setup()
{
    pinMode(this->acPin,INPUT);
    vref = readVref();
}

void ACCurrent_S::setHandleExceed(HandleRaw handleExceed, float maxAccValue)
{
    this->_handleExceed = handleExceed;
    this->_maxAccValue = maxAccValue;
}

void ACCurrent_S::setHandleLess(HandleRaw handleLess, float minAccValue)
{
    this->_handleLess = handleLess;
    this->_minAccValue = minAccValue;
}

float ACCurrent_S::readVref()
{
    long result;
#if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined (__AVR_ATmega328P__)
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__) || defined(__AVR_AT90USB1286__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
    ADCSRB &= ~_BV(MUX5);   // Without this the function always returns -1 on the ATmega2560 http://openenergymonitor.org/emon/node/2253#comment-11432
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
#endif
#if defined(__AVR__)
    delay(2);                                        // Wait for Vref to settle
    ADCSRA |= _BV(ADSC);                             // Convert
    while (bit_is_set(ADCSRA, ADSC));
    result = ADCL;
    result |= ADCH << 8;
    result = 1126400L / result;  //1100mV*1024 ADC steps http://openenergymonitor.org/emon/node/1186
    return result;
#elif defined(__arm__)
    return (3300);          //Arduino Due
#else
    return (3300);          //Guess that other un-supported architectures will be running a 3.3V!
#endif
}

void ACCurrent_S::update()
{
    unsigned int peakVoltage = 0;  
    unsigned int voltageVirtualValue = 0;  //Vrms
    for (int i = 0; i < 5; i++)
    {
    peakVoltage += analogRead(this->acPin);   //read peak voltage
    delay(1);
    }
    peakVoltage = peakVoltage / 5;   
    voltageVirtualValue = peakVoltage * 0.707;  	//change the peak voltage to the Virtual Value of voltage

    /*The circuit is amplified by 2 times, so it is divided by 2.*/
    voltageVirtualValue = (voltageVirtualValue * this->vref / 1024) / 2;  

    this->accurrtntValue = (voltageVirtualValue * ACTectionRange)/1000;

    if(this->_handleExceed && this->accurrtntValue > this->_maxAccValue)
    {
        this->_handleExceed(this->accurrtntValue);
    }
    if(this->_handleLess && this->accurrtntValue < this->_minAccValue)
    {
        this->_handleLess(this->accurrtntValue);
    }
}

float ACCurrent_S::getValue()
{
    return this->accurrtntValue;
}
