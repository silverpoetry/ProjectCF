#pragma once

#include "IncludeList.h"
#define OBSTACLE_DISTANCE 10
extern int Graph[10][10][6];
struct Pos {
	int x = -1, y = -1;
};
struct myCar {
	Pos pos;
	//int node_x = 0, node_y = 0;
	int orientation = 0; 
};
extern int Road;

void MT_GraphInit ();

int MT_Main ();
void MT_ProbeObstacle (Pos now);
void MT_ExploreMaze (Pos rog, Pos def);
/* 
1-left 2-right 3-left_front 4-front
*/

