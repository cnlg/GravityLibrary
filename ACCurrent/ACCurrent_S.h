#ifndef _ACCurrent_S_H_
#define _ACCurrent_S_H_

#define ACTectionRange 20
typedef void (*HandleFunc)(float accValue);

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
    void setHandleExceed(HandleFunc handleExceed, float maxAccValue);
    void setHandleLess(HandleFunc handleLess, float minAccValue);
    
private:
    HandleFunc _handleExceed = 0;
    HandleFunc _handleLess = 0;
    float _maxAccValue;
    float _minAccValue;
    float readVref();
    float vref;
    int   acPin; 
    float accurrtntValue; 
};

#endif
