#include <Arduino.h>
#include <MPU6050.h>
#include <I2Cdev.h>
#include <Wire.h>
MPU6050 mpu;
extern void failureBeeps();
int16_t ax, ay, az;
int16_t gx, gy, gz;
bool hasLiftoff;
extern int systemState;
const float gyroScale = 131.0; // Gyro scale factor for full-scale range ±250 degrees per second
float dt = 0.01;         // Time interval between readings
int numReadings = 1000;

float gyroXDrift = 0.0;
float gyroYDrift = 0.0;
float gyroZDrift = 0.0;

float angleX = 0.0;
float angleY = 0.0;
float angleZ = 0.0;


void mpuInit()
{
    Serial.println("");
    Serial.println("Connecting to MPU6050 IMU...");
    Wire.begin();
    mpu.initialize();
    if (!mpu.testConnection())
    {
        Serial.println("IMU connection failed...");
        failureBeeps();
        while (1)
            ;
    }
    Serial.println("");
    Serial.println("IMU ready.");
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

int calibrateGyro() {
    Serial.println("Calibrating gyro...");
  
    for (int i = 0; i < numReadings; i++) {
        int16_t gyroX, gyroY, gyroZ;
        mpu.getRotation(&gyroX, &gyroY, &gyroZ);
        
        gyroXDrift += gyroX / 131.0;
        gyroYDrift += gyroY / 131.0;
        gyroZDrift += gyroZ / 131.0;
        tone(2, 2500);
        delay(10);
        tone(2, 1500);
    }
    noTone(2);
    gyroXDrift /= numReadings;
    gyroYDrift /= numReadings;
    gyroZDrift /= numReadings;
    
    Serial.println("Gyro calibration complete.");
    return gyroXDrift, gyroYDrift, gyroZDrift;
}




int getAngle() {
    float gyroXRate = (gx / gyroScale) - gyroXDrift;
    float gyroYRate = (gy / gyroScale) - gyroYDrift;
    float gyroZRate = (gz / gyroScale) - gyroZDrift;
  
    
    angleX += gyroXRate * dt * 3;
    angleY += gyroYRate * dt * 3;
    angleZ += gyroZRate * dt * 3;
    
    return angleX, angleY, angleZ;
}



int IMUAccelUpdate()
{
    mpu.getAcceleration(&ax, &ay, &az);
    return ax, ay, az;
}
int IMUGyroUpdate()
{
    mpu.getRotation(&gx, &gy, &gz);
    return gx, gy, gz;
}
void detectLiftoff()
{
    if (systemState == 0 && ay >= 25000)
    {
        systemState++;
        hasLiftoff = true;
    }
}