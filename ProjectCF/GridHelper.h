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



template<class T>
struct Queue {

	T Array[40];
	int front0 = 0, back = 0;

	void push(T elm) {
		Array[back] = elm;
		back = (back + 1) % 39;
	}
	void pop() {
		++front0;
		front0 = front0  % 39;
	}
	T front() {
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

void gh_exit(Pos p);

bool GridHelper_SearchRoadAdventure(Pos from, Pos to);


const int map_sensor[4] = { 1,3,0,2 };

//各侧障碍物的距离与格数对应法则
const int obstacle_range[4][2][2] = {
   {{20,120},{121,280}},
   {{5,90},{90,230}},
   {{3,45},{45,75}},
   {{3,90},{90,230}}

};
extern myCar car;
void GridHelper_Go(Pos from, Pos to);
void GridHelper_GoAdventure(Pos from, Pos to);
int GridHelper_CntManhattonDist(Pos from, Pos to);
/* 
1-left 2-right 3-left_front 4-front
*/

 // !asd