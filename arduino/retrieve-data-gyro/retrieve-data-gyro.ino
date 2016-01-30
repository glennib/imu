#include <Wire.h>
#include <stdint.h>

#include "Gpio.h"
#include "Error.h"
#include "Debug.h"
#include "Spi.h"
#include "Itg.h"

#define RAD2DEG 57.29577951
#define MIN_FROM (-32768)
#define MAX_FROM 32767
#define MIN_TO (-2000)
#define MAX_TO 2000

void initialize()
{
    Serial.begin(9600);
    delay(10000);
    spi_init();
    itg_init();
    gpio_init();
    Serial.println("Ready.");
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
                    Serial.print(ITG_ADR, HEX);
                    Serial.print(": 0x");
                    Serial.print(C1);
                    Serial.print(C2);
                    Serial.print(" = 0b");
                    Serial.println(spi_read_setting(ITG_ADR, adr), BIN);
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
    }*/
    


    unsigned long last_time = millis();
    while(1)
    //for (uint32_t mlc = 0; mlc < 6000; mlc++)
    {
        debug("Waiting for interrupt");
        while(digitalRead(ITG_INT_PIN) == 1)
        {/*
            delay(1000);
            Serial.print("Pin ");
            Serial.print(ITG_INT_PIN);
            Serial.print(": ");
            Serial.print(digitalRead(ITG_INT_PIN));
            Serial.print(". Int status: 0b");
            Wire.beginTransmission(ITG_ADR);
            Wire.write(ITG_INT_STATUS);
            Wire.endTransmission();
            Wire.requestFrom(ITG_ADR, 1);
            Serial.print(Wire.read(), BIN);
            Serial.print(". Available after read: ");
            Serial.print(Wire.available());

            Serial.print('\n');*/
        }
        debug("Interrupt happened");
        unsigned long current_time = millis();

        Serial.print("Elapsed: ");
        Serial.println(current_time - last_time);

        last_time = current_time;

        // interrupt has occured

        Wire.beginTransmission(ITG_ADR);
        Wire.write(ITG_GYRO_XOUT_H);
        Wire.endTransmission();

        Wire.requestFrom(ITG_ADR, ITG_DATA_BYTES);

        uint8_t itg_data[ITG_DATA_BYTES];
        uint8_t counter = 0;
        while (Wire.available())
        {
            itg_data[counter] = Wire.read();
            counter++;
        }
        if (counter != ITG_DATA_BYTES)
        {
            error("Unexpected counter value");
        }

        int16_t value = (int16_t) ( (itg_data[0] << 8) | (itg_data[1]) );
        const int32_t FROM_SIZE = MAX_FROM - MIN_FROM + 1;
        const float TO_SIZE = MAX_TO - MIN_TO;
        float theta = (float)(value - MIN_FROM) / FROM_SIZE * TO_SIZE + MIN_TO;

        Serial.println(theta, 4);
    }
    
    while(1) { ; }
}



void loop()
{
    // keeping this empty...
}
