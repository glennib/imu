#pragma once

#include "Auxiliary.h"

// Settings:


#define ADXL_OFSX_V 0x00
#define ADXL_OFSY_V 0x00
#define ADXL_OFSZ_V 0x00

#define ADXL_LOW_POWER_V 0b0 // shift 4
#define ADXL_RATE_V 0b1010 // shift 0 - 100 Hz
#define ADXL_BW_RATE_V ( (ADXL_LOW_POWER_V << 4) | (ADXL_RATE_V) )

#define ADXL_LINK_V 0 // shift 5
#define ADXL_AUTO_SLEEP_V 0 // shift 4
#define ADXL_MEASURE_V 1 // shift 3
#define ADXL_SLEEP_V 0 // shift 2
#define ADXL_WAKEUP_V 0b00 // shift 0
#define ADXL_POWER_CTL_V ( (ADXL_LINK_V << 5) | (ADXL_AUTO_SLEEP_V << 4) | (ADXL_MEASURE_V << 3) | (ADXL_SLEEP_V << 2) | (ADXL_WAKEUP_V) )

#define ADXL_INT_ENABLE_V 0b00000010 // only watermark

#define ADXL_INT_MAP_V 0x00

#define ADXL_INT_INVERT_V 0 // shift 5
#define ADXL_FULL_RES_V 0 // shift 3
#define ADXL_JUSTIFY_V 0 // shift 2
#define ADXL_RANGE_V 0b00 // shift 0 - +-16g
#define ADXL_DATA_FORMAT_V ( (ADXL_INT_INVERT_V << 5) | (ADXL_FULL_RES_V << 3) | (ADXL_JUSTIFY_V << 2) | (ADXL_RANGE_V) )

#define ADXL_FIFO_MODE_V 0b01 // shift 6 - fifo
#define ADXL_TRIGGER_V 0 // shift 5
#define ADXL_SAMPLES_V 1 // shift 0 - [1, 31]
#define ADXL_FIFO_CTL_V ( (ADXL_FIFO_MODE_V << 6) | (ADXL_TRIGGER_V << 5) | (ADXL_SAMPLES_V) )

// Addresses:

#define ADXL_ADR 0x53

#define ADXL_DEVID 0x00
#define ADXL_OFSX 0x01E
#define ADXL_OFSY 0x1F
#define ADXL_OFSZ 0x20
#define ADXL_BW_RATE 0x2C
#define ADXL_POWER_CTL 0x2D
#define ADXL_INT_ENABLE 0x2E
#define ADXL_INT_MAP 0x2F
#define ADXL_INT_SOURCE 0x30
#define ADXL_DATA_FORMAT 0x31
#define ADXL_DATAX0 0x32
#define ADXL_DATAX1 0x33
#define ADXL_DATAY0 0x34
#define ADXL_DATAY1 0x35
#define ADXL_DATAZ0 0x36
#define ADXL_DATAZ1 0x37
#define ADXL_FIFO_CTL 0x38
#define ADXL_FIFO_STATUS 0x39

#define ADXL_DATA_BYTES (ADXL_DATAZ1 - ADXL_DATAX0 + 1)


#define ADXL_MEAN -0.0477f
#define ADXL_SIGMA2 2.8877e-5

void adxl_init();

float adxl_get_data();

