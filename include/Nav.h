#include <Arduino.h>

extern int16_t ax, ay, az;
extern int16_t gx, gy, gz;
extern float altitudeAGL;
extern float temp;
extern float altitude;
extern float pressure;

void navUpdate()
{
    altitude = BMPAltitudeUpdate();
    pressure = BMPPressureUpdate();
    temp = BMPTempUpdate();
    IMUAccelUpdate();
    IMUGyroUpdate();
    altitudeAGL = BMPAltitudeUpdateAGL();
}
