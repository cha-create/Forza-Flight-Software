#include <Arduino.h>
#include <PWMServo.h>

PWMServo servox;
PWMServo servoy;

void TVCInitalize()
{
    servox.attach(3);
    servoy.attach(5);
    servoy.write(55);
    servox.write(55);
    delay(125);
    servox.write(95);
    delay(125);
    servox.write(55);
    delay(125);
    servoy.write(95);
    delay(125);
    servoy.write(55);
    delay(125);
    servox.write(15);
    delay(125);
    servox.write(55);
    delay(125);
    servoy.write(15);
    delay(500);
    servox.write(15);
    delay(125);
    servox.write(55);
    servoy.write(55);
}

void TVCCenter()
{
    servox.write(55);
    servoy.write(55);
}