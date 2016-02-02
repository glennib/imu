#pragma once

#include "Auxiliary.h"

// Settings:
#define ITG_SMPLRT_DIV_V 79 // Divider - should be 79 to get 100 Hz data [0,255]

#define ITG_FS_SEL_V 0x03 // 0x03 for proper operation - shift 3
#define ITG_DLPF_CFG_V 0 // For 8 kHz internal sampling (256Hz lp filter)
#define ITG_DLPF_FS_V ( (ITG_FS_SEL_V << 3) | ITG_DLPF_CFG_V )

#define ITG_ACTL_V 1 // Interrupt active low (1) - shift 7
#define ITG_OPEN_V 1 // Open collector (1) - shift 6
#define ITG_LATCH_INT_EN_V 1 // Latch until cleared (1) - shift 5
#define ITG_INT_ANYRD_2CLEAR_V 1 // Latch clear method any register read (1) - shift 4
#define ITG_ITG_RDY_EN_V 0 // Dont enable interrupt when device is ready (0) - shift 2
#define ITG_RAW_RDY_EN_V 1 // Enable interrupt when data is ready (1) - shift 0
#define ITG_INT_CFG_V ( (ITG_ACTL_V << 7) | (ITG_OPEN_V << 6) | (ITG_LATCH_INT_EN_V << 5) | (ITG_INT_ANYRD_2CLEAR_V << 4) | (ITG_ITG_RDY_EN_V << 2) | ITG_RAW_RDY_EN_V )

#define ITG_H_RESET_V 0 // Shift 7
#define ITG_SLEEP_V 0 // Shift 6
#define ITG_STBY_XG_V 0 // X not in standby mode (0) - Shift 5
#define ITG_STBY_YG_V 1 // Y in standby (1) - Shift 4
#define ITG_STBY_ZG_V 1 // Z in standby (1) - Shift 3
#define ITG_CLK_SEL_V 1 // Make X clock source (1) - Shift 0
#define ITG_PWR_MGM_V ( (ITG_H_RESET_V << 7) | (ITG_SLEEP_V << 6) | (ITG_STBY_XG_V << 5) | (ITG_STBY_YG_V << 4) | (ITG_STBY_ZG_V << 3) | (ITG_CLK_SEL_V) )

#define ITG_DATA_BYTES 2

// Addresses:

#define ITG_ADR 0b1101000

#define ITG_WHO_AM_I 0x00
#define ITG_SMPLRT_DIV 0x15
#define ITG_DLPF_FS 0x16
#define ITG_INT_CFG 0x17
#define ITG_INT_STATUS 0x1A
#define ITG_TEMP_OUT_H 0x1B
#define ITG_TEMP_OUT_L 0x1C
#define ITG_GYRO_XOUT_H 0x1D
#define ITG_GYRO_XOUT_L 0x1E
#define ITG_GYRO_YOUT_H 0x1F
#define ITG_GYRO_YOUT_L 0x20
#define ITG_GYRO_ZOUT_H 0x21
#define ITG_GYRO_ZOUT_L 0x22
#define ITG_PWR_MGM 0x3E

// Math:

#define ITG_MIN_FROM (-32768)
#define ITG_MAX_FROM 32767
#define ITG_MIN_TO (-2000)
#define ITG_MAX_TO 2000

#define ITG_MEAN 0.0163f
#define ITG_SIGMA2 2.4272e-6

#define ITG_LSB2RADS 0.00127406f

void itg_init();

float itg_get_data();
