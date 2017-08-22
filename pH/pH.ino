#include "pH.h"

Ph ph;

void test(double value)
{}

void setup()
{
    Serial.begin(9600);
    ph.setPin(A2);
    ph.setOffset(0);
    ph.setup();
    ph.setHandleL(test,10);
    ph.setHandleM(test,4);
    
}

void loop()
{
    ph.update();
    Serial.println(ph.getValue());
}
