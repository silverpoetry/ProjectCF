#pragma once

#include "IncludeList.h"


void Move_GotimeWithoutStop(int speed, int time);
void Move_GoSpeed (int speed1, int speed2);

//void Move_GoBack (int speed, int time);
void Move_Stop ();


int Move_RotateLeft(void);
int Move_RotateRight (void);

void Move_Refresh();
//void Move_GoSpeed(int speed1 ,	int	 speed2);
void Move_KeepRate();
void Move_Gotime(int speed1,int speed2, int time);
void Move_GoStraightTime(int speed, int time);
void Move_Fucker();

void Move_TurnLeft (int speed);