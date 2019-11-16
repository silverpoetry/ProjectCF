#pragma once



#include "Types.h"

extern int Graph[8][8][6];

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

	queueitem Array[64];
	int front0 = 0, back = 0;

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


void GridHelper_Init2();
void GridHelper_Init();


void GridHelper_InitGraph();
void GridHelper_Detect ();
Pos GridHelper_PositionConverter(Pos p);



bool SavePeopleReadyforEntrance();
bool SavePeopleBackReadytoGoBlind();
bool SavePeopleReturnHome();


const int map_sensor[4] = { 1,3,0,2 };

//各侧障碍物的距离与格数对应法则
const int obstacle_range[4][2][2] = {
   {{20,120},{121,270}},
   {{5,90},{90,230}},
   {{3,45},{45,75}},
   {{3,90},{90,230}}

};
extern myCar car;
void GridHelper_Go(Pos from, Pos to);
int GridHelper_CntManhattonDist(Pos from, Pos to);
/* 
1-left 2-right 3-left_front 4-front
*/

 // !asd