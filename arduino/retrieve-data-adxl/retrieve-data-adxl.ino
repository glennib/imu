#include <Wire.h>
#include <stdint.h>

#include "Adxl.h"
#include "Gpio.h"
#include "Error.h"
#include "Debug.h"
#include "Spi.h"

#define RAD2DEG 57.29577951


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

    /*
    char buf[10];
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
                    Serial.print("MAN - 0x");
                    Serial.print(ADXL_ADR, HEX);
                    Serial.print(": 0x");
                    Serial.print(C1);
                    Serial.print(C2);
                    Serial.print(" = 0b");
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
            memset(buf, 0, 10);
            counter = 0;
        }
    }
    */
    
    
    uint8_t adxl_data[ADXL_SAMPLES_V][ADXL_DATA_BYTES];
    //uint8_t fifo_data[ADXL_SAMPLES_V];
    
    while (1)
    //for (int main_loop_counter = 0; main_loop_counter < 300; main_loop_counter++) // gather 300 * 20 = 6000 samples = 60s of samples
    {
        //debug("Waiting for interrupt");
        
        while (digitalRead(ADXL_INT_PIN) == 0)
        {
            // wait for the interrupt
            //debug("Inside wait loop");
            //Serial.println(digitalRead(ADXL_INT_PIN));
            //delay(1000);
        }
        
        //debug("Interrupt occurred");
        
        for (int i = 0; i < ADXL_SAMPLES_V; i++)
        {            
            // Start from DATAX0
            Wire.beginTransmission(ADXL_ADR);
            Wire.write(ADXL_DATAX0);
            Wire.endTransmission();

            // request bytes
            Wire.requestFrom(ADXL_ADR, ADXL_DATA_BYTES);
            uint8_t counter = 0;
            
            while (Wire.available())
            {
                adxl_data[i][counter] = Wire.read();
                counter++;
            }
            if (counter != ADXL_DATA_BYTES)
            {
                error("Unexpected counter value");
            }
            //Wire.endTransmission();
            delayMicroseconds(5);
            // get fifo data
            //fifo_data[i] = spi_read_setting(ADXL_ADR, ADXL_FIFO_STATUS);
        }
        
        for (int i = 0; i < ADXL_SAMPLES_V; i++)
        {
            //Serial.print("Last accelerometer values:");

            int16_t values[3];
            int32_t sz2 = 0;
            for (int j = 0; j < 3; j++)
            {
                uint8_t lsb = adxl_data[i][2*j];
                uint8_t msb = adxl_data[i][2*j+1];
                int16_t val = (int16_t) ( (msb << 8) | (lsb) );
                values[j] = val;
                sz2 += (uint32_t)(((uint32_t)val) * ((uint32_t)val));
                //Serial.print(" ");
                //Serial.print(val, DEC);
            }            
            //Serial.print(" Size = ");
            float sz = sqrt(sz2);
            //Serial.print(sz);
            float y = (float) values[1];
            float z = (float) values[2];
            float theta = atan2(y, -z) * RAD2DEG;
            //Serial.print(" Angle = ");
            Serial.print(theta, 4);
            //Serial.print(" FIFO: 0b");
            //Serial.print(fifo_data[i], BIN);

            Serial.print('\n');
        }
    }

    while(1) { ; }
}



void loop()
{
    // keeping this empty...
}
