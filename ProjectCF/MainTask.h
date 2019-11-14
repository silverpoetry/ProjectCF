#pragma once

#include "IncludeList.h"
#define OBSTACLE_DISTANCE 10
extern int Graph[8][8][6];
struct Pos {
	int X = -1, Y = -1;
	Pos (int x = 0, int y = 0) {
		this->X = x;
		this->Y = y;
	}
	bool operator ==(const Pos& p)
	{
		return X == p.X&&Y == p.Y;
	}
/*	void operator =(const Pos& p)
	{
		 (X = p.X , Y = p.Y);
	}*/
};
struct myCar {
	Pos Position;
	//int node_x = 0, node_y = 0;

	int Orientation = 0; //
};
extern int MainTask_Road;

void MainTask_GraphInit ();

int MT_Main ();
void Maintask_Init2();
void Maintask_Init();
void MainTask_GraphInit();
void MainTask_ProbeObstacle ();

/* 
1-left 2-right 3-left_front 4-front
*/

