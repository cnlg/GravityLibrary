#ifndef _GENERALANALOGSENSOR_H_ 
#define _GENERALANALOGSENSOR_H_ 


typedef void (*pFunc)(int value);

class GeneralAnalogSensor
{
public:
    GeneralAnalogSensor();
    ~GeneralAnalogSensor();
public:
    void setPin(uint8_t pin, uint8_t mode);
    int  getValue();
    void setValue(int value);
    void update(unsigned long interval = 0);
    void setHandleM(pFunc handleM,int maxvalue);
    void setHandleL(pFunc handleL,int minvalue);

private:
    uint8_t _pin;
    int _value;
    int _maxValue;
    int _minValue;
    pFunc _handleM;
    pFunc _handleL;
    unsigned long _lastTime;

    void handleCallback();

};


#endif
