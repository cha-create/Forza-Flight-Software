#include <Arduino.h>
extern int systemState;
extern bool errorboi;
unsigned long timerInterval = 1000;  // Interval for the timers (in milliseconds)
unsigned long lastUpdateTime = 0;
enum State {
  STATE_INITIAL,
  STATE_TIMER1,
  STATE_TIMER2
};

State currentState = STATE_INITIAL;

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
    if (systemState == 3)
    {
       // landing beeps and boops
            unsigned long currentTime = millis();

        if (currentTime - lastUpdateTime >= timerInterval) {
        lastUpdateTime = currentTime;

        switch (currentState) {
            case STATE_INITIAL:
            digitalWrite(9, HIGH);
            tone(2, 2000);
            currentState = STATE_TIMER1;
            break;

            case STATE_TIMER1:
            digitalWrite(9, LOW);
            digitalWrite(6, HIGH);
            tone(2, 2500);
            currentState = STATE_TIMER2;
            break;

            case STATE_TIMER2:
            digitalWrite(6, LOW);
            digitalWrite(9, HIGH);
            tone(2, 2000);
            currentState = STATE_TIMER1;
            break;
        }
        }           
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
}