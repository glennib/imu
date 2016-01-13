void spi_init()
{
    Wire.begin();
}

void spi_set_confirm(const uint8_t adr, const uint8_t reg, const uint8_t val)
{
    // Write
    debug("Writing setting...");
    Wire.beginTransmission(adr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
    // Read
    debug("Reading setting...");
    Wire.beginTransmission(adr);
    Wire.write(reg);
    Wire.endTransmission();
    Wire.requestFrom((uint8_t)adr, (uint8_t)1);
    
    if (Wire.available())
    {
        uint8_t read = Wire.read();
        
        if (!(val == read))
        {
            error("SPI setting not confirmed");
        }
    }
    else
    {
        error("Cannot read SPI setting");
    }
}
