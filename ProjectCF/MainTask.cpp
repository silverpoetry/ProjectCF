#include "MainTask.h"

int Graph[8][8][6];
//0, 1, 2, 3 for front, right, back, left
int MainTask_Road = 0;
bool checked_list[8][8];

myCar car;

int getPosition (int dir)
{
	return (car.Orientation + dir) % 4;
}
int SetDisabled (int dir)
{
	const int step = 0;
	int pos = getPosition (dir);
	if (pos == 0)Graph[car.Position.X][car.Position.Y + step][pos] = -1;
	if (pos == 1)Graph[car.Position.X - step][car.Position.Y][pos] = -1;
	if (pos == 2)Graph[car.Position.X][car.Position.Y - step][pos] = -1;
	if (pos == 3)Graph[car.Position.X + step][car.Position.Y][pos] = -1;
}
int SetDisabled (int dir, int step)
{
	int pos = getPosition (dir);
	if (pos == 0)Graph[car.Position.X][car.Position.Y + step][pos] = -1;
	if (pos == 1)Graph[car.Position.X - step][car.Position.Y][pos] = -1;
	if (pos == 2)Graph[car.Position.X][car.Position.Y - step][pos] = -1;
	if (pos == 3)Graph[car.Position.X + step][car.Position.Y][pos] = -1;
}
int SetVal (int dir, int step, int val)
{
	int pos = getPosition (dir);
	if (pos == 0)Graph[car.Position.X][car.Position.Y + step][pos] = val;
	if (pos == 1)Graph[car.Position.X - step][car.Position.Y][pos] = val;
	if (pos == 2)Graph[car.Position.X][car.Position.Y - step][pos] = val;
	if (pos == 3)Graph[car.Position.X + step][car.Position.Y][pos] = val;

}

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
				if (j == 1 && k == 2) Graph[i][j][k] = -1;
				if (j == 6 && k == 0) Graph[i][j][k] = -1;
				if (i == 1 && k == 1) Graph[i][j][k] = -1;
				if (i == 6 && k == 3) Graph[i][j][k] = -1;

				if (i == j + 1 && (k == 1 || k == 2)) {
					//下半场对应的中场线方向不可访问
					Graph[i][j][k] = -1;
				}
				else if (j == i && (k == 3 || k == 4)) {
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
	Graph[5][7][2] = 1;
	Graph[0][2][3] = 1;
	Graph[7][5][1] = 1;
}
int MainTask_CntManhattonDist (Pos from, Pos to) {
	return abs (from.X - to.X) + abs (from.Y - to.Y);
}
int map_sensor[4] = { 1,3,0,2 };
void MainTask_ProbeObstacle ()
{
	for (int k = 0; k <= 3; k++)
	{
		if (k == 2)continue;
		if (Graph[car.Position.X][car.Position.Y][k] == 0) {
			int distance = Distance_Get (map_sensor[k]);
			if (distance < OBSTACLE_DISTANCE)
			{
				SetDisabled (k);
			}
			else
			{
				SetVal (k, 0, 1);
				if (distance < 2 * OBSTACLE_DISTANCE)
					SetDisabled (k, 1);
				else SetVal (k, 1, 1);
			}
		}
	}


}

Pos link_last[9][9];
Pos path[100];
int pathlength;
struct queueitem
{
	Pos to;
	Pos from;
};
struct BFSQueue {
private:
	queueitem Array[1000];
	int front0 = 0, back = 0;
public:
	void push (queueitem elm) {
		Array[++back] = elm;
	}
	void pop () {
		++front0;
	}
	queueitem front () {
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

Pos min_dist_pos = { 1, 1 };
int min_dist = 1000;
void MT_UpdateMinDistPos (Pos tmp, Pos to) {
	if (MainTask_CntManhattonDist (tmp, to) < min_dist) {
		min_dist_pos = tmp;
		min_dist = MainTask_CntManhattonDist (tmp, to);
	}
}
bool BFS (Pos from, Pos to) {

	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			checked_list[i][j] = 0, link_last[i][j] = { i,j };
	pathlength = 0;


	BFSQueue q;
	q.push ({ from,from });

	min_dist_pos = from;
	min_dist = MainTask_CntManhattonDist (min_dist_pos, to);
//	checked_list[from.X][from.Y] = 1;

	//默认不搜索身后的点，如果无路可走再把身后的点加进去
	while (!q.empty ()) {
		Pos now = q.front ().to;

		if (checked_list[now.X][now.Y]) { q.pop ();  continue; }

		link_last[now.X][now.Y] = q.front ().from;
		q.pop ();
		checked_list[now.X][now.Y] = 1;
		if (now.X == to.X && now.Y == to.Y)break;
		Pos tmp; int dist = 0;
		// 0, 1, 2, 3 for front, right, back, left
		if ((now.Y < 7) && (!checked_list[now.X][now.Y + 1]) && (Graph[now.X][now.Y][0] == 1)) {
			if (getPosition (2) == 0)
				continue;
			tmp.X = now.X;
			tmp.Y = now.Y + 1;
			q.push ({ tmp,now });
			MT_UpdateMinDistPos (tmp, to);
		}
		if ((now.Y > 0) && (!checked_list[now.X][now.Y - 1]) && (Graph[now.X][now.Y][2] == 1)) {
			if (getPosition (2) == 2)
				continue;
			tmp.X = now.X;
			tmp.Y = now.Y - 1;
			q.push ({ tmp,now });
			MT_UpdateMinDistPos (tmp, to);
		}
		if ((now.X < 7) && (!checked_list[now.X + 1][now.Y]) && (Graph[now.X][now.Y][3] == 1)) {
			if (getPosition (2) == 3)
				continue;
			tmp.X = now.X + 1;
			tmp.Y = now.Y;
			q.push ({ tmp,now });
			MT_UpdateMinDistPos (tmp, to);
		}
		if ((now.X > 0) && (!checked_list[now.X - 1][now.Y]) && (Graph[now.X][now.Y][1] == 1)) {
			if (getPosition (2) == 1)
				continue;
			tmp.X = now.X - 1;
			tmp.Y = now.Y;
			q.push ({ tmp,now });
			MT_UpdateMinDistPos (tmp, to);
		}
	}
	Pos p;
	bool flag = 0;
	if (checked_list[to.X][to.Y]) {
		p = to;
		flag = 1;
	}
	else {
		p = min_dist_pos;
	}
	if (p == from) {
		Pos back_pos;
		int dir = getPosition (2);
		// 0, 1, 2, 3 for front, right, back, left
		if (dir == 0) {
			back_pos = { p.X, p.Y + 1 };
		}
		else if (dir == 1) {
			back_pos = { p.X - 1, p.Y };
		}
		else if (dir == 2) {
			back_pos = { p.X, p.Y - 1};
		}
		else if (dir == 3) {
			back_pos = { p.X + 1, p.Y };
		}
		path[1] = p;
		path[2] = back_pos;
		return 0;
	}
	else {
		path[++pathlength] = p; 
	}
	while (!(link_last[p.X][p.Y] == p))
	{
		pathlength++;
		path[pathlength] = p;
		p = link_last[p.X][p.Y];
	}
	Rep (i, 1, pathlength / 2)
	{
		Pos tmp = path[i];
		path[i] = path[pathlength - i + 1];
		path[pathlength - i + 1] = tmp;
	}
	return flag;

}
void MainTask_Goto (Pos p) {
	//转弯并走到下一个点
}

bool if_possibile = 0;

//主循环改成了DFS，暂未处理：走到头没路了，倒回来一个格，选择下一条路（也就是回溯的过程）
//如果继续BFS套BFS，在当前找不到路BFS需要返回多条路径，目前只返回了距离最近的点的路径
void MainTask_ExploreMaze (Pos org, Pos def, int depth) {
	if (org == def) {
		return;
	}
	if (!if_possibile) {
		if_possibile = BFS (org, def);
	}
	if (if_possibile) {
		MainTask_Goto (path[depth+1]);
	}
	else {
		MainTask_Goto (path[2]);
	}
	MainTask_ProbeObstacle ();
	MainTask_ExploreMaze (car.Position, def, depth + if_possibile);
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
int MainTask(){
	Pos org = { 2, 0 }, def = { 7, 5 };
	MainTask_ExploreMaze (org, def, 1);
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