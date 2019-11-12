#pragma once

#include "IncludeList.h"
#define OBSTACLE_DISTANCE 10
extern int Graph[10][10][6];
struct Pos {
	int X = -1, Y = -1;
	bool operator ==(const Pos& p)
	{
		return X == p.X&&Y == p.Y;
	}
};
struct myCar {
	Pos Position;
	//int node_x = 0, node_y = 0;

	int Orientation = 0; //
};
extern int MainTask_Road;

void MainTask_GraphInit ();

int MT_Main ();
void MainTask_ProbeObstacle ();
void MainTask_ExploreMaze (Pos rog, Pos def);
/* 
1-left 2-right 3-left_front 4-front
*/

