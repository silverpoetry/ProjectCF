#include "MainTask.h"

int Graph[10][10][6];
//0, 1, 2, 3 for front, back, left, right
int MainTask_Road = 0;
bool checked_list[8][8];

myCar car;

struct Queue {
private:
	Pos Array[100];
	int front0 = 0, back = 0;
public:
	void push (Pos elm) {
		Array[++back] = elm;
	}
	void pop () {
		++front0;
	}
	Pos front () {
		return Array[front0];
	}
	void clear () {
		front0 = 0;
		back = 0;
	}
	bool empty () {
		return front0 == back;
	}
};
void MainTask_GraphInit () {

	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			checked_list[i][j] = 0;
			for (int k = 0; k < 4; k++) {
				if (i == 0 || i == 7 || j == 0 || j == 7) {
					//边界上的点四个方向都初始化为不可访问
					Graph[i][j][k] = -1;
				}
				else if (j == 1 && k == 1) Graph[i][j][k] = -1;
				else if (j == 6 && k == 0) Graph[i][j][k] = -1;
				else if (i == 1 && k == 3) Graph[i][j][k] = -1;
				else if (i == 6 && k == 2) Graph[i][j][k] = -1;

				else if (i == j + 1 && (k == 1 || k == 3)) {
					//下半场对应的中场线方向不可访问
					Graph[i][j][k] = -1;
				}
				else if (j == i + 1 && (k == 2 || k == 2)) {
					//上半场对应的中场线方向不可访问
					Graph[i][j][k] = -1;
				}
				else
					Graph[i][j][k] = 0;
			}
		}
	}

	//迷宫入口的四个边界点方向可访问
	Graph[2][0][0] = 1;
	Graph[5][7][1] = 1;
	Graph[0][2][2] = 1;
	Graph[7][5][3] = 1;
}
int MT_CntManhattanDist (Pos from, Pos to) {
	return abs (from.X - to.X) + abs (from.Y - to.Y);
}
void MainTask_ProbeObstacle (Pos now) {
	if (Graph[now.X][now.Y][1] == 0) {
		int distance = Distance_Get (1);
		if (distance < OBSTACLE_DISTANCE) {
			Graph[now.X][now.Y][car.Orientation] = -1;
		}
		else {
			Graph[now.X][now.Y][car.Orientation] = 1;
			if (distance < 2 * OBSTACLE_DISTANCE) {
				if (car.Orientation == 0)
					Graph[now.X][now.Y + 1][car.Orientation] = 0;
				else if (car.Orientation == 1)
					Graph[now.X][now.Y - 1][car.Orientation] = 0;
				else if (car.Orientation == 2)
					Graph[now.X - 1][now.Y][car.Orientation] = 0;
				else if (car.Orientation == 3)
					Graph[now.X + 1][now.Y][car.Orientation] = 0;

			}
			//else if()
		}
	}

	//0-2, 1-3, 2-1, 3-0
	if (Graph[now.X][now.Y][2] == 0) {
		int distance = Distance_Get (2);
		bool flag = (distance >= OBSTACLE_DISTANCE);

		if (car.Orientation == 0)
			Graph[now.X][now.Y][2] = flag;
		else if (car.Orientation == 1)
			Graph[now.X][now.Y][3] = flag;
		else if (car.Orientation == 2)
			Graph[now.X][now.Y][1] = flag;
		else if (car.Orientation == 3)
			Graph[now.X][now.Y][0] = flag;
		/*
				if (flag == 1) {
					flag = (distance >= 2 * OBSTACLE_DISTANCE);
					if (car.orientation == 0)
						Graph[now.x + 1][now.y][2] = flag;
					else if (car.orientation == 1)
						Graph[now.x - 1][now.y][3] = flag;
					else if (car.orientation == 2)
						Graph[now.x][now.y - 1][1] = flag;
					else if (car.orientation == 3)
						Graph[now.x][now.y + 1][0] = flag;
				}*/
	}

	//0-3, 1-2, 2-0, 3-1
	if (Graph[now.X][now.Y][3] == 0) {
		int distance = Distance_Get (3);
		bool flag = (distance >= OBSTACLE_DISTANCE);

		if (car.Orientation == 0)
			Graph[now.X][now.Y][3] = flag;
		else if (car.Orientation == 1)
			Graph[now.X][now.Y][2] = flag;
		else if (car.Orientation == 2)
			Graph[now.X][now.Y][0] = flag;
		else if (car.Orientation == 3)
			Graph[now.X][now.Y][1] = flag;
		/*		if (flag == 1) {
					flag = (distance >= 2 * OBSTACLE_DISTANCE);
					if (car.orientation == 0)
						Graph[now.x - 1][now.y][3] = flag;
					else if (car.orientation == 1)
						Graph[now.x - 1][now.y][2] = flag;
					else if (car.orientation == 2)
						Graph[now.x][now.y - 1][0] = flag;
					else if (car.orientation == 3)
						Graph[now.x][now.y + 1][1] = flag;
				}
			}*/

	}
}
bool BFS (Pos from, Pos to) {
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			checked_list[i][j] = 0;

	Queue q;
	q.push (from);
	checked_list[from.X][from.Y] = 1;
	while (!q.empty ()) {
		Pos now = q.front ();
		q.pop ();
		checked_list[now.X][now.Y] = 1;
		Pos tmp;
		if ((!checked_list[now.X][now.Y + 1]) && (Graph[now.X][now.Y][0] == 1)) {
			tmp.X = now.X;
			tmp.Y = now.Y + 1;
			q.push (tmp);
		}
		if ((!checked_list[now.X][now.Y - 1]) && (Graph[now.X][now.Y][1] == 1)) {
			tmp.X = now.X;
			tmp.Y = now.Y - 1;
			q.push (tmp);
		}
		if ((!checked_list[now.X + 1][now.Y]) && (Graph[now.X][now.Y][2] == 1)) {
			tmp.X = now.X + 1;
			tmp.Y = now.Y;
			q.push (tmp);
		}
		if ((!checked_list[now.X - 1][now.Y]) && (Graph[now.X][now.Y][3] == 1)) {
			tmp.X = now.X - 1;
			tmp.Y = now.Y;
			q.push (tmp);
		}
	}
	if (!checked_list[to.X][to.Y])
		return 0;
	return 1;
}
void MainTask_ExploreMaze (Pos org, Pos def) {
	Queue q;
	q.push (org);
	checked_list[org.X][org.Y] = 1;
	while (!q.empty ()) {
		Pos now = q.front ();
		q.pop ();
		bool possibility = BFS (now, def);
		if (!possibility) {
			
		}
	}
}
int MT_Pos2Node (int& x, int& y) {
	/*
	2,0: 106,15贴左边   85,15贴左开始拐（左轮刚过）78,24正好进入 81,14 开始拐（在入口中央）
	0,2:
*/

	if ((x >= 65 && x <= 80) && (y >= 17 && y <= 20)) {
		x = 2, y = 0;
	}

}
/*
int MT_FindEntrance (int road) {
	while (1) {
		//if (Zigbee_MessageRecord ()) {
		Zigbee_MessageRecord ();
		int x = Car[1].pos.X, y = Car[1].pos.Y;
		Debugger_SetWatch ("x", x);
		Debugger_SetWatch ("y", y);
		Move_GoSpeed (SPEED, SPEED);
		if (x <= 82) {
			Move_Stop ();
			delay (500);
			Move_TurnLeft (150);
			while (1) {
				//if (Manager_Time_TakeTime (30, 30)) {

				if (Huidu_IsLine (2)) {
					Move_Stop ();
					delay (500);
					return;
				}
				//}
			}

		}
		//MT_Pos2Node (x, y);
	//}
	}
	//MT_FindExit (2, 0);
}

int MT_Pos2Node (int& x, int& y) {
	/*
	2,0: 106,15贴左边   85,15贴左开始拐（左轮刚过）78,24正好进入 81,14 开始拐（在入口中央）
	0,2:


	if ((x >= 65 && x <= 80) && (y >= 17 && y <= 20)) {
		x = 2, y = 0;
	}

}
int MT_FreeMaze (void) {
	if (Zigbee_MessageRecord ()) {
		int x = Car[0].pos.X, y = Car[0].pos.Y;
		MT_Pos2Node (x, y);
	}
}

int MT_Main () {
	MT_FindEntrance (1);
	MT_FindExit (2, 0);
	return 1;
}*/