#pragma once

#include "IncludeList.h"
#define OBSTACLE_DISTANCE 35
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

};
struct myCar {
	Pos Position;
	int Orientation = 0; 
};
struct queueitem
{
	Pos to;
	Pos from;
};
struct Queue {
private:
	queueitem Array[1000];
	int front0 = 0, back = 0;
public:
	void push(queueitem elm) {
		Array[back++] = elm;
	}
	void pop() {
		++front0;
	}
	queueitem front() {
		return Array[front0];
	}
	void clear() {
		front0 = 0;
		back = 0;
	}
	bool empty() {
		return front0 == back;
	}
};


void Maintask_Init2();
void Maintask_Init();


void MainTask_GraphInit();
void MainTask_ProbeObstacle ();
Pos MainTask_PositionConverter(Pos p);



bool SavePeopleReadyforEntrance();
bool SavePeopleBackReadytoGoBlind();
bool SavePeopleReturnHome();


const int map_sensor[4] = { 1,3,0,2 };

//各侧障碍物的距离与格数对应法则
const int obstacle_range[4][2][2] = {
   {{3,45},{45,75}},
   {{3,45},{45,75}},
   {{3,45},{45,75}},
   {{3,45},{45,75}}

};
/* 
1-left 2-right 3-left_front 4-front
*/

