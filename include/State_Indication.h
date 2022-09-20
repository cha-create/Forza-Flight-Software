#include <Arduino.h>
#include <UniversalTimer.h>
UniversalTimer lightDelay(1000, true);
UniversalTimer lightDelay1(1000, true);
extern int systemState;
extern bool errorboi;

void State_Indication()
{

    if (systemState == 0)
    {
        digitalWrite(9, HIGH);
        digitalWrite(6, HIGH);
    }

    if (systemState == 1)
    {

        digitalWrite(9, HIGH);

        digitalWrite(6, LOW);
    }
    if (systemState == 2)
    {
        digitalWrite(9, LOW);
        digitalWrite(6, HIGH);
    }
    // if (systemState == 3)
    // {
    //     digitalWrite(9, HIGH);
    //     digitalWrite(6, HIGH);
    // }
    if (systemState == 3)
    {
        lightDelay.start();
        while (!lightDelay.check())
        {
            digitalWrite(9, HIGH);
            tone(2, 2000);
        }
        noTone(2);
        digitalWrite(9, LOW);
        lightDelay.stop();
        lightDelay1.start();
        while (!lightDelay1.check())
        {
            digitalWrite(6, HIGH);
            tone(2, 2500);
        }
        noTone(2);
        digitalWrite(6, LOW);
        lightDelay1.stop();
    }
}

void startupBeeps()
{
    tone(2, 1262);
    delay(250);
    tone(2, 1523);
    delay(250);
    tone(2, 2047);
    delay(250);
    noTone(2);
}

void failurelights()
{
    digitalWrite(6, HIGH);
    digitalWrite(9, LOW);
    delay(250);
    digitalWrite(6, LOW);
    digitalWrite(9, HIGH);
    delay(250);
}

void failureBeeps()
{
    tone(2, 2047);
    delay(150);
    tone(2, 1523);
    delay(150);
    tone(2, 1262);
    delay(150);
    noTone(2);
    tone(2, 2047);
    delay(150);
    tone(2, 1523);
    delay(150);
    tone(2, 1262);
    delay(150);
    noTone(2);
    tone(2, 2047);
    delay(150);
    tone(2, 1523);
    delay(150);
    tone(2, 1262);
    delay(150);
    noTone(2);
    errorboi = true;
    while (errorboi == true)
    {
        failurelights();
    }
}
