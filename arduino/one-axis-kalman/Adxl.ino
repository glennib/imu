void adxl_init()
{
    spi_set_confirm(ADXL_ADR, ADXL_POWER_CTL, ADXL_POWER_CTL_V & 0b11110111);
    
    spi_set_confirm(ADXL_ADR, ADXL_INT_ENABLE, 0);
    
    spi_set_confirm(ADXL_ADR, ADXL_OFSX, ADXL_OFSX_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_OFSY, ADXL_OFSY_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_OFSZ, ADXL_OFSZ_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_BW_RATE, ADXL_BW_RATE_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_INT_MAP, ADXL_INT_MAP_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_DATA_FORMAT, ADXL_DATA_FORMAT_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_FIFO_CTL, ADXL_FIFO_CTL_V);

    // Empty FIFO
    for (uint8_t i = 0; i < 32; i++)
    {
        spi_read_setting(ADXL_ADR, ADXL_DATAX0);
    }
    
    spi_set_confirm(ADXL_ADR, ADXL_INT_ENABLE, ADXL_INT_ENABLE_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_POWER_CTL, ADXL_POWER_CTL_V);
}

float adxl_get_data()
{
    uint8_t adxl_data[ADXL_DATA_BYTES];
    Wire.beginTransmission(ADXL_ADR);
    Wire.write(ADXL_DATAX0);
    Wire.endTransmission();

    // request bytes
    Wire.requestFrom(ADXL_ADR, ADXL_DATA_BYTES);
    uint8_t counter = 0;
    
    while (Wire.available())
    {
        adxl_data[counter] = Wire.read();
        counter++;
    }
    if (counter != ADXL_DATA_BYTES)
    {
        error("Unexpected counter value");
    }
    delayMicroseconds(5);
    int16_t values[3];
    for (int j = 0; j < 3; j++)
    {
        uint8_t lsb = adxl_data[2*j];
        uint8_t msb = adxl_data[2*j+1];
        int16_t val = (int16_t) ( (msb << 8) | (lsb) );
        values[j] = val;
    }
    float y = (float) values[1];
    float z = (float) values[2];
    float theta = atan2(y, -z) * RAD2DEG;
}

