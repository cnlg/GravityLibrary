#ifndef _GENERALDIGITALSENSOR_H_ 
#define _GENERALDIGITALSENSOR_H_ 


typedef void (*pFunc)(void);

class GeneralDigitalSensor
{
public:
    GeneralDigitalSensor();
    ~GeneralDigitalSensor();
public:
    void    setPin(uint8_t pin, uint8_t mode);
    void    setValue(uint8_t value);
    uint8_t getValue();


private:
    uint8_t _pin;
};


#endif
