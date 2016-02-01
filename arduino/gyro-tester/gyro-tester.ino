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

    float theta = 0;
    
    while(1)
    {
        while(digitalRead(ITG_INT_PIN == 1))
        {
            // Just wait.
        }

        volatile float gyro_measurement = itg_get_data() - ITG_MEAN;
        
        theta += gyro_measurement * KALMAN_DT;

        Serial.println(theta * RAD2DEG);
    }
}


void loop() {
  
}
