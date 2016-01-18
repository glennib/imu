void spi_init()
{
    Wire.begin();
}

void spi_set_confirm(const uint8_t adr, const uint8_t reg, const uint8_t val)
{
    // Write
    //debug("Writing setting...");
    Wire.beginTransmission(adr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
    // Read
    //debug("Reading setting...");
    Wire.beginTransmission(adr);
    Wire.write(reg);
    Wire.endTransmission();

    delay(5);
    
    Wire.requestFrom((uint8_t)adr, (uint8_t)1);
    
    if (Wire.available())
    {
        uint8_t read = Wire.read();        
        if (!(val == read))
        {
            error("SPI setting not confirmed");
            Serial.println("SPI setting not confirmed");
            Serial.print("0x");
            Serial.print(reg, HEX);
            Serial.print(": Tried to write ");
            Serial.print(val, HEX);
            Serial.print(", read 0x");
            Serial.println(read, HEX);
            while(1)
            {
                
            }
        }
        else
        {
            Serial.print("0x");
            Serial.print(adr, HEX);
            Serial.print(": 0x");
            Serial.print(reg, HEX);
            Serial.print(" = 0b");
            Serial.println(read, BIN);
        }
    }
    else
    {
        error("Cannot read SPI setting");
    }
}

uint8_t spi_read_setting(const uint8_t adr, const uint8_t reg)
{
    //debug("Reading setting...");
    Wire.beginTransmission(adr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)adr, (uint8_t)1);
    
    if (Wire.available())
    {
        return Wire.read();
    }
    else
    {
        error("Cannot read SPI setting");
    }
}

