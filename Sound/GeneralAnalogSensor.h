#ifndef _GENERALANALOGSENSOR_H_ 
#define _GENERALANALOGSENSOR_H_ 


class GeneralAnalogSensor
{
public:
    GeneralAnalogSensor();
    ~GeneralAnalogSensor();
public:
    void setPin(uint8_t pin, uint8_t mode);
    int getValue();
    void setValue(int value);

private:
    uint8_t _pin;
};


#endif
