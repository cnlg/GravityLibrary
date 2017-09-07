#include "pH.h"

Ph ph;
double phValue = 0;

void setup()
{
    Serial.begin(9600);
    ph.setPin(A2);
    ph.setOffset(0);
}

void loop()
{
    ph.update();
    phValue = ph.getValue();
    Serial.println(phValue);
}
