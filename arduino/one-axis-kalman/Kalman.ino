
void kalman_init()
{
    kalman_initialized = 0;
}

float *kalman_update(float z, float u)
{
    static float P_pri[2][2];
    static float x_pri[2];
    
    if (!kalman_initialized)
    {
        kalman_initialized = 1;

        P_pri[0][0] = KALMAN_P_PRI_11;
        P_pri[0][1] = KALMAN_P_PRI_12;
        P_pri[1][0] = KALMAN_P_PRI_21;
        P_pri[1][1] = KALMAN_P_PRI_22;

        x_pri[0] = KALMAN_X_PRI_1;
        x_pri[1] = KALMAN_X_PRI_2;
        
    }
    float pkpri11r = 1 / (P_pri[0][0] + KALMAN_R);
    float K[2] = {P_pri[0][0] * pkpri11r, P_pri[1][0] * pkpri11r};
    float x[2] = {x_pri[0] + K[0] * (z - x_pri[1]),
                  x_pri[1] + K[1] * (z - x_pri[1])};
    float helpp1 = 1 - P_pri[0][0] * pkpri11r;
    float helpp2 = - P_pri[1][0] * pkpri11r;
    float P[2][2] = {
        {helpp1 * P_pri[0][0], helpp1 * P_pri[0][2]},
        {helpp2 * P_pri[0][0] + P_pri[1][0], helpp2 * P_pri[0][1] + P_pri[1][1]}
    };
    P_pri[0][0] = KALMAN_DT * (P[1][1] * KALMAN_DT - P[0][1] - P[1][0]) + P[0][0] + KALMAN_Q_11;
    P_pri[0][1] = KALMAN_Q_12;
    P_pri[1][0] = KALMAN_Q_21;
    P_pri[1][1] = KALMAN_Q_22;

    x_pri[0] = -x[1] * KALMAN_DT + x[0];
    x_pri[1] = 0;
    return x;
}

