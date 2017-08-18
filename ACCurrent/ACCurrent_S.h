#ifndef _ACCurrent_S_H_
#define _ACCurrent_S_H_

#define ACTectionRange 20
typedef (*HandleRaw)(float accValue);

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
    void setHandleExceed(HandleRaw handleExceed, float maxAccValue);
    void setHandleLess(HandleRaw handleLess, float minAccValue);
    
private:
    HandleRaw _handleExceed = 0;
    HandleRaw _handleLess = 0;
    float _maxAccValue;
    float _minAccValue;
    float readVref();
    float vref;
    int   acPin; 
    float accurrtntValue; 
};

#endif
