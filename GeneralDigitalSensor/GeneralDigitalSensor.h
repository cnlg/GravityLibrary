#ifndef _GENERALDIGITALSENSOR_H_ 
#define _GENERALDIGITALSENSOR_H_ 

typedef void (*pFunc)(uint8_t value);

class GeneralDigitalSensor
{
public:
    GeneralDigitalSensor();
    ~GeneralDigitalSensor();
public:
    void    setPin(uint8_t pin, uint8_t mode);
    void    setValue(uint8_t value);
    uint8_t getValue();
    void    update(unsigned long interval = 0);
    void    setHandleM(pFunc handleM,int maxValue);
    void    setHandleL(pFunc handleL,int minValue);
   

private:
    uint8_t _pin;
    uint8_t _value;
    pFunc _handleM;
    pFunc _handleL;
    int _maxValue;
    int _minValue;
    unsigned long _lastTime;

    void handleCallback();
    
};


#endif
