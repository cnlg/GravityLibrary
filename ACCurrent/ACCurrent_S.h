#ifndef _ACCurrent_S_H_
#define _ACCurrent_S_H_

#define ACTectionRange 20

class ACCurrent_S
{
public:
    ACCurrent_S();
    ~ACCurrent_S();

public:
    void setPin(int pin);
    void setup();
    void update();
    float getValue();
    void setInterval(unsigned long interval);

private:
    float readVref();
    void  calculateAcc();
    float _vref;
    int   _pin; 
    float _accurrtntValue; 
    double _interval;
};

#endif

