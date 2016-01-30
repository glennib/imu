#define KALMAN_Q_11 0.1f
#define KALMAN_Q_12 0.0f
#define KALMAN_Q_21 0.0f
#define KALMAN_Q_22 0.1f

#define KALMAN_R 0.1f

#define KALMAN_P_PRI_11 0.1f
#define KALMAN_P_PRI_12 0.0f
#define KALMAN_P_PRI_21 0.0f
#define KALMAN_P_PRI_22 0.1f

#define KALMAN_X_PRI_1 0.1f
#define KALMAN_X_PRI_2 0.1f

#define KALMAN_DT 0.01f

uint8_t kalman_initialized;

void kalman_init();
float *kalman_update(float accel_measurement, float gyro_measurement);
