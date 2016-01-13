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
    
    spi_set_confirm(ADXL_ADR, ADXL_INT_ENABLE, ADXL_INT_ENABLE_V);
    
    spi_set_confirm(ADXL_ADR, ADXL_POWER_CTL, ADXL_POWER_CTL_V);
}

