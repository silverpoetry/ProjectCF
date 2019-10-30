#pragma once
#include "IncludeList.h"
void PL_GoWithoutStop();
void PL_GoLineTime(int time);
void PL_GoCrossTurnLeft();
int PL_Position (int sensor_a, int sensor_b, int sensor_c, int sensor_d);
int PL_PIDCorrection (int opt);
int PL_FindCenter (void);
int PL_CrossRoad (int opt);
int PL_GoStop (void);
void PL_goline (int basic1, int basic2);

extern double PID_KP , PID_KI , PID_KD ;