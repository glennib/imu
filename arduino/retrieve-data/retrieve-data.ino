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

    char buf[50];
    while (1)
    {
        uint8_t counter = 0;
        while (Serial.available())
        {
            buf[counter++] = Serial.read();
        }
        if (counter >= 3)
        {
            // should be consistent with 2 address characters and a newline
            if (buf[2] == '\n')
            {
                char C1 = buf[0];
                char C2 = buf[1];
                uint8_t adr = 0;
                if ( ( (C1 >= '0' && C1 <= '9') || (C1 >='A' && C1 <= 'F') ) && ( (C2 >= '0' && C2 <= '9') || (C2 >='A' && C2 <= 'F') ) )
                {
                    if (C1 >= 'A')
                    {
                        adr = (C1 - 'A' + 10) << 4;
                    }
                    else
                    {
                        adr = (C1 - '0') << 4;
                    }

                    if (C2 >= 'A')
                    {
                        adr |= (C2 - 'A' + 10);
                    }
                    else
                    {
                        adr |= (C2 - '0');
                    }
                    Serial.print(C1);
                    Serial.print(C2);
                    Serial.print(" = ");
                    Serial.println(spi_read_setting(ADXL_ADR, adr), BIN);
                }
                else
                {
                    debug("Wrong format. Try again.");
                }
            }
            else
            {
                debug("Error. Try again.");
                
            }
            memset(buf, 0, 50);
            counter = 0;
        }
    }
    
    /*
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
        
    }*/
}



void loop()
{
    // keeping this empty...
}
