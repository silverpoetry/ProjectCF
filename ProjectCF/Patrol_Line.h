#pragma once
#include "IncludeList.h"
void PL_GoWithoutStop();
void PL_GoLineTime(int time);
void PL_GoCrossTurnLeft();
void PL_PIDCorrection(int opt);
void PL_CrossRoad(int opt);
int PL_GoStop (void);
//void PL_goline (int basic1, int basic2);
void PL_GoBlind (int opt);
void PL_GoBackBlind (int opt);
void PL_GoBackStop ();
void PL_GoCrossTurnRight ();
void PL_GoBlind(int opt, int speed);
extern double PID_KP , PID_KI , PID_KD ;
void PL_GoBackStop ();
enum CorssRoad
{
	CrossRoad_Left ,
	CrossRoad_Right 
};