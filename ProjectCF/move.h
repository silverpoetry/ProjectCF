#pragma once

#include "IncludeList.h"


void Move_GoStraight (int speed, int time);
void Move_GoStraight (int speed);//time = infinite

void Move_GoBack (int speed, int time);

void Move_TurnRight (int time);
void Move_TurnLeft (int time);

void Move_RotateRight (int time, int angle);
void Move_RotateLeft (int time, int angle);

void Move_Refresh();
void Move_GoSpeed(int speed1 ,	int	 speed2);
void Move_KeepRate();