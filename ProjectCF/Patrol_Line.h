#pragma once
#include "IncludeList.h"

int PL_Position (int sensor_a, int sensor_b, int sensor_c, int sensor_d);
int PL_PIDCorrection (int opt);
int PL_FindCenter (void);
int PL_CrossRoad (int opt);
void Patrol (void);

void PL_goline (int basic1, int basic2);