#pragma once
#include "IncludeList.h"

int PL_Position (int sensor_a, int sensor_b, int sensor_c, int sensor_d);
int PL_PIDCorrection (int opt);
int PL_FindCenter (void);
int PL_CrossRoad (int opt);

void PL_goline (int basic1, int basic2);

double PID_KP = 0.2, PID_KI = 0.1, PID_KD = 0.3;