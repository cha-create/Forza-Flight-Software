#include <Arduino.h>
#include <PWMServo.h>
#include <PID_v1.h>
PWMServo servox;
PWMServo servoy;
double xinput, xoutput, setpoint;
double zinput, zoutput;
double Kp=2, Ki=0, Kd=2;
int servoxAngle;
int servozAngle;
PID xPID(&xinput, &xoutput, &setpoint, Kp, Ki, Kd, DIRECT);
PID zPID(&zinput, &zoutput, &setpoint, Kp, Ki, Kd, DIRECT);


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
    // init PID
    xinput = angleX;
    zinput = angleZ;
    setpoint = 0;
    xPID.SetMode(AUTOMATIC);
    zPID.SetMode(AUTOMATIC);

}

void TVCLoop() {
    xinput = angleX;
    zinput = angleZ;
    xPID.Compute();
    zPID.Compute();
    servoxAngle = map(xoutput, 0, 100, 75, 35);
    servozAngle = map(zoutput, 0, 100, 75, 35);
    servox.write(servoxAngle);
    servoy.write(servozAngle);
    delay(25);
    Serial.print(xoutput);
    Serial.print(", ");
    Serial.println(zoutput);
}



void TVCCenter()
{
    servox.write(55);
    servoy.write(55);
}