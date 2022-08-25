#include <Arduino.h>
#include <UniversalTimer.h>
extern float altitudeAGL;
extern int timeSinceLiftoff;
// extern int SITLAltitudeAGL;
UniversalTimer pyroDelay(1000, false);

void allPyrosLow()
{
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
}

void FirePyro1()
{
    pyroDelay.start();

    while (!pyroDelay.check())
    {
        digitalWrite(30, HIGH);
    }
    digitalWrite(30, LOW);
}

void FirePyro2()
{
    pyroDelay.start();

    while (!pyroDelay.check())
    {
        digitalWrite(31, HIGH);
    }
    if (pyroDelay.getTimerValue() == 0)
    {
        digitalWrite(31, LOW);
    }
}

void fireBothPyros()
{
    digitalWrite(30, HIGH);
    digitalWrite(31, HIGH);
    delay(1000);
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
}
void detectChutes()
{
    if (systemState == 2 && BMPAltitudeUpdateAGL() <= 10 && hitApogee && timeSinceLiftoff >= 3500)
    {
        FirePyro1();
        systemState++;
    }
}