#pragma once

#include "Auxiliary.h"
#include "Itg.h"
#include "Adxl.h"

#define KALMAN_Q ITG_SIGMA2

#define KALMAN_R ADXL_SIGMA2

#define KALMAN_P_PRI_11 0.1f
#define KALMAN_P_PRI_12 0.0f
#define KALMAN_P_PRI_21 0.0f
#define KALMAN_P_PRI_22 0.1f

#define KALMAN_X_PRI_1 0.0f
#define KALMAN_X_PRI_2 0.1f

#define KALMAN_DT 0.01f

uint8_t kalman_initialized;

void kalman_init();
void kalman_update(float accel_measurement, float gyro_measurement);
