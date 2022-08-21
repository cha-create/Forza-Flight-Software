#include <Arduino.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include <Wire.h>
MPU6050 mpu;

int16_t ax, ay, az;
int16_t gx, gy, gz;
bool hasLiftoff;
extern int systemState;
void mpuInit()
{
    Serial.print("Connecting to MPU6050 IMU");
    Wire.begin();
    mpu.initialize();
    Serial.println(mpu.testConnection() ? "\nIMU Ready..." : "\nIMU connection failed...");
}

void printVals_IMU_x10()
{
    for (int i = 0; i < 10; i++)
    {
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        String motion = ax + ay + az + gx + gy + gz;
        Serial.println(motion);
        delay(250);
    }
}

int IMUAccelUpdate()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    return ax, ay, az;
}
int IMUGyroUpdate()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    return gx, gy, gz;
}
void detectLiftoff()
{
    if (systemState == 0 && ay >= 30000)
    {
        systemState++;
        hasLiftoff = true;
    }
}