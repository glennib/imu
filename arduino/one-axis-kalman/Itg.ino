void itg_init()
{
    spi_set_confirm(ITG_ADR, ITG_SMPLRT_DIV, ITG_SMPLRT_DIV_V);
    spi_set_confirm(ITG_ADR, ITG_DLPF_FS, ITG_DLPF_FS_V);
    spi_set_confirm(ITG_ADR, ITG_PWR_MGM, ITG_PWR_MGM_V);
    spi_set_confirm(ITG_ADR, ITG_INT_CFG, ITG_INT_CFG_V);
}

float itg_get_data()
{
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
    const int32_t FROM_SIZE = ITG_MAX_FROM - ITG_MIN_FROM + 1;
    const float TO_SIZE = ITG_MAX_TO - ITG_MIN_TO;
    float theta = (float)(value - ITG_MIN_FROM) / FROM_SIZE * TO_SIZE + ITG_MIN_TO;
    return theta;
}

