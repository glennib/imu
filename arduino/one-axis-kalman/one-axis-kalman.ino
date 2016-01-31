#include <Wire.h>
#include <stdint.h>

#include "Adxl.h"
#include "Itg.h"
#include "Gpio.h"
#include "Error.h"
#include "Debug.h"
#include "Spi.h"
#include "Kalman.h"
#include "Auxiliary.h"

void initialize()
{
    Serial.begin(9600);
    delay(10000);
    spi_init();
    itg_init();
    adxl_init();
    gpio_init();
    kalman_init();
    Serial.println("Ready");
}


void setup() // this is main().
{
    initialize();

    while(1)
    {
        while(digitalRead(ITG_INT_PIN == 1))
        {
            // Just wait.
        }

        volatile float gyro_measurement = itg_get_data() - ITG_MEAN;
        
        while(digitalRead(ADXL_INT_PIN == 0))
        {
            // Just wait.
        }

        volatile float accel_measurement = adxl_get_data() - ADXL_MEAN;

        float x[2] = {0, 0};
        kalman_update(accel_measurement, gyro_measurement, x);
        Serial.print("Accelerometer: ");
        Serial.print(accel_measurement);
        Serial.print(" Gyroscope: ");
        Serial.print(gyro_measurement);
        Serial.print(" Angle: ");
        Serial.print(x[0] * RAD2DEG);
        Serial.print('\n');
    }
}


void loop() {
  
}
