#include <Arduino.h>
#include <PWMServo.h>
#include <PID_v1.h>
PWMServo servox;
PWMServo servoy;
double setpoint = 0;
double xinput, xoutput;
double zinput, zoutput;
double Kp=0.45;
double Ki=0.02;
double Kd=0.35;
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
    xPID.SetOutputLimits(-24, 24);
    zPID.SetOutputLimits(-24, 24);
    xPID.SetSampleTime(25);
    zPID.SetSampleTime(25);
}

void TVCLoop() {
    xinput = angleX;
    zinput = angleZ;
    xPID.Compute();
    zPID.Compute();
    servoxAngle = map(xoutput, -24, 24, 75, 35);
    servozAngle = map(zoutput, -24, 24, 35, 75);
    servox.write(servoxAngle);
    servoy.write(servozAngle);
    // Serial.print(xoutput);
    // Serial.print(", ");
    // Serial.println(zoutput);
}



void TVCCenter()
{
    servox.write(55);
    servoy.write(55);
}