#include <Wire.h>
#include <stdint.h>

#include "Adxl.h"
#include "Gpio.h"
#include "Error.h"
#include "Debug.h"
#include "Spi.h"
#include "Itg.h"
#include "Kalman.h"

#define RAD2DEG 57.29577951

void initialize()
{
    Serial.begin(9600);
    delay(10000);
    spi_init();
    itg_init();
    adxl_init();
    gpio_init();
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

        float gyro_measurement = itg_get_data();
        
        while(digitalRead(ADXL_INT_PIN == 0))
        {
            // Just wait.
        }

        float accel_measurement = adxl_get_data();

        
    }
}


void loop() {
  
}
