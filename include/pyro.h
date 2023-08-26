#include <Arduino.h>
#include <arduino-timer.h>
extern float altitudeAGL;
extern int timeSinceLiftoff;
extern float maxAltitude;
bool pyro1Fired = false;
// extern int SITLAltitudeAGL;
bool pyroActive = false;
extern Timer<3> timer;
void allPyrosLow()
{
    digitalWrite(30, LOW);
    digitalWrite(31, LOW);
}

bool pyro1Low(void *) {
    pyroActive = false;
    digitalWrite(30, LOW);
    return true;
}

void FirePyro1()
{
    digitalWrite(30, HIGH);
    pyro1Fired = true;
    pyroActive = true;
    timer.in(2000, pyro1Low);
}

void FirePyro2()
{
    // pyroDelay.start();

    // while (!pyroDelay.check())
    // {
    //     digitalWrite(31, HIGH);
    // }
    // if (pyroDelay.getTimerValue() == 0)
    // {
    //     digitalWrite(31, LOW);
    // }
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
    if (systemState == 2 && BMPAltitudeUpdateAGL() <= (maxAltitude - 5.00) && hitApogee && timeSinceLiftoff >= 3500)
    {
        FirePyro1();
        systemState++;
    }
}