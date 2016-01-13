#include <Wire.h>
#include <stdint.h>

#include "Adxl.h"
#include "Gpio.h"
#include "Error.h"
#include "Debug.h"
#include "Spi.h"


void initialize()
{
    Serial.begin(9600);
    delay(10000);
    spi_init();
    gpio_init();
    adxl_init();
}


void setup()   // treat this as a main()
{
    initialize();
    
    uint8_t adxl_data[ADXL_SAMPLES_V][6];
    
    while (1)
    {
        debug("Waiting for interrupt");
        
        while (digitalRead(ADXL_INT_PIN) == 0)
        {
            // wait for the interrupt
            debug("Inside wait loop");
            Serial.println(digitalRead(ADXL_INT_PIN));
            delay(1000);
        }
        
        debug("Interrupt occurred");
        Wire.beginTransmission(ADXL_ADR);
        Wire.write(ADXL_DATAX0);
        Wire.endTransmission();
        
        for (int i = 0; i < ADXL_SAMPLES_V; i++)
        {
            Wire.requestFrom(ADXL_ADR, 6);
            uint8_t counter = 0;
            
            while (Wire.available())
            {
                counter++;
                adxl_data[i][counter] = Wire.read();
            }
        }
        
    }
}



void loop()
{
    // keeping this empty...
}
