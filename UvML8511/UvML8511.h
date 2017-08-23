#ifndef _UVML8511_H_
#define _UVML8511_H_

typedef void (*pFunc)(float uvIntensity);

class UvML8511
{

public:
    UvML8511();
    ~UvML8511();
public:
    void  setPin(int pin);
    void  setup();
    void  update();
    float getUvValue();
    float getVoltageValue();
    void setHandleM(pFunc handleM,float maxUvValue);
    void setHandleL(pFunc handleL,float minUvValue);

private:
    int   _pin;
    float _voltage;
    float _uvIntensity;
    pFunc _handleM;
    pFunc _handleL;
    float _maxUvValue;
    float _minUvValue;
    int averageAnalogRead();
    float mapFloat(float x, float in_min, float in_max, float out_min, float out_max);
    
};


#endif
