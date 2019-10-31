#pragma once
#include "IncludeList.h"
void PL_GoWithoutStop();
void PL_GoLineTime(int time);
void PL_GoCrossTurnLeft();

void PL_CrossRoad(int opt);
int PL_GoStop (void);
void PL_goline (int basic1, int basic2);

extern double PID_KP , PID_KI , PID_KD ;
enum CorssRoad
{
	CrossRoad_Left ,
	CrossRoad_Right 
};