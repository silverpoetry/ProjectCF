#include "MainTask.h"

int Graph[8][8][6];
//0, 1, 2, 3 for front, right, back, left
int MainTask_Road = 0;
bool checked_list[8][8];

myCar car;
int getPosition(int dir)
{
	return (car.Orientation + dir) % 4;
}
void SetVal(int dir, int step, int val)
{
	int pos = getPosition(dir), backpos = (pos + 2) % 4;

	if (pos == 0)Graph[car.Position.X][car.Position.Y + step + 1][backpos] = Graph[car.Position.X][car.Position.Y + step][pos] = val;
	if (pos == 1)Graph[car.Position.X - step - 1][car.Position.Y][backpos] = Graph[car.Position.X - step][car.Position.Y][pos] = val;
	if (pos == 2)Graph[car.Position.X][car.Position.Y - step - 1][backpos] = Graph[car.Position.X][car.Position.Y - step][pos] = val;
	if (pos == 3)Graph[car.Position.X + step + 1][car.Position.Y][backpos] = Graph[car.Position.X + step][car.Position.Y][pos] = val;

}
int GetVal(int dir, int step)
{
	int pos = getPosition(dir);

	if (pos == 0)return  Graph[car.Position.X][car.Position.Y + step][pos];
	if (pos == 1)return  Graph[car.Position.X - step][car.Position.Y][pos];
	if (pos == 2)return Graph[car.Position.X][car.Position.Y - step][pos];
	if (pos == 3)return Graph[car.Position.X + step][car.Position.Y][pos];

}
void SetDisabled(int dir, int step)
{
	SetVal(dir, step, -1);
}
void SetDisabled(int dir)
{
	SetDisabled(dir, 0);
}


Pos MainTask_PositionConverter(Pos p)
{
	Pos startpoint = { 30,30 };
	int blockwidth = 30;
	p.X -= startpoint.X;
	p.Y -= startpoint.Y;
	Pos ret;
	p.X = (int)(((float)(p.X)) / blockwidth + 0.5) + 1;
	p.Y = (int)(((float)(p.Y)) / blockwidth + 0.5) + 1;
	ret.Y = p.X;
	ret.X = 7 - p.Y;
	return ret;


}
int MainTask_CntManhattonDist(Pos from, Pos to) {
	return abs(from.X - to.X) + abs(from.Y - to.Y);
}



void MainTask_GraphInit() {

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

				if (i == j + 1 && (k == 0 || k == 1)) {
					//下半场对应的中场线方向不可访问
					Graph[i][j][k] = -1;
				}
				else if (j == i && (k == 2 || k == 3)) {
					//上半场对应的中场线方向不可访问
					Graph[i][j][k] = -1;
				}
				else {}
					
			}
		}
	}

	//迷宫入口的四个边界点方向可访问
	Graph[2][0][0] = 1;
	Graph[2][1][2] = 1;
	Graph[2][0][1] = -1;
	Graph[2][0][2] = -1;
	Graph[2][0][3] = -1;
	Graph[5][7][2] = 1;
	Graph[5][6][0] = 1;
	Graph[5][7][0] = -1;
	Graph[5][7][1] = -1;
	Graph[5][7][3] = -1;
	Graph[0][2][3] = 1;
	Graph[1][2][1] = 1;
	Graph[0][2][1] = -1;
	Graph[0][2][2] = -1;
	Graph[0][2][0] = -1;
	Graph[7][5][1] = 1;
	Graph[6][5][3] = 1;
	Graph[7][5][0] = -1;
	Graph[7][5][2] = -1;
	Graph[7][5][3] = -1;
}
void Maintask_Init2()
{
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			Graph[i][j][0] = Graph[i][j][1] = Graph[i][j][2] = Graph[i][j][3] = 1;
		}
	}
	MainTask_GraphInit();


}
void Maintask_Init()
{
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			Graph[i][j][0] = Graph[i][j][1] = Graph[i][j][2] = Graph[i][j][3] = 0;
		}
	}
	MainTask_GraphInit();

}


int MainTask_GetDistanceLevel(int dir)
{
	int dis = Distance_Get(map_sensor[dir]);
	if (obstacle_range[dir][0][0]< dis&dis< obstacle_range[dir][0][1] )
	{
		//近在眼前
		return 1;
	}
	else if (obstacle_range[dir][1][0] < dis&dis < obstacle_range[dir][1][1])
	{
		return 2;
	}
	else
	{
		return 3;
	}
}
void MainTask_ProbeObstacle()
{

	//k代表方向的循环
	for (int k = 0; k <= 3; k++)
	{
		//后面不用探测
		if (k == 2)continue;
		int dislevel = MainTask_GetDistanceLevel(k);
		//n代表距离的循环
		for (int n = 1; n <= 2; n++)
		{

			//已探测直接滚蛋
			if (GetVal(k, n - 1) != 0)break;

			if (n<dislevel)SetVal(k, n - 1, 1);
			else
			{
				SetDisabled(k, n - 1);
				break;
			}		
		

		}
	}


}

Pos link_last[9][9];
Pos path[100];
int maplength[9][9];
int pathlength;
Pos min_dist_pos = { 1, 1 };
int min_dist = 1000;
void MT_UpdateMinDistPos(Pos tmp, Pos to) {
	//内部路线长度权值0.5
	int length = MainTask_CntManhattonDist(tmp, to) + maplength[tmp.X][tmp.Y];
	if (length < min_dist) {
		min_dist_pos = tmp;
		min_dist = length;
	}
}
void MainTask_MakePath(Pos p)
{
	pathlength = maplength[p.X][p.Y];
	
	Dwn(i, pathlength, 1)
	{
		path[i] = p;
		p = link_last[p.X][p.Y];
	}	
}
bool MainTask_SearchRoad(Pos from, Pos to) {

	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			checked_list[i][j] = 0, link_last[i][j] = { i,j },maplength[i][j]=0;
	pathlength = 0;
	
	min_dist_pos = { 1,1 };
	min_dist = 1000;

	Queue q;
	q.push({ from,from });


	while (!q.empty()) {

		Pos now = q.front().to;
		Pos last = q.front().from;
		if (checked_list[now.X][now.Y]) { q.pop();  continue; }

		checked_list[now.X][now.Y] = 1;
		//记录来路
		link_last[now.X][now.Y] = last;
		maplength[now.X][now.Y] = maplength[last.X][last.Y]+1;
		
		q.pop();
		
		
		//如果存在未探索点，将其加入搜索
		bool b = false;
		for (int i = 0; i <= 3; i++)b =( b || (Graph[now.X][now.Y][i] == 0));
		if (b)MT_UpdateMinDistPos(now, to);
		//找到
		if (now.X == to.X && now.Y == to.Y)break;

		Pos tmp; int dist = 0;
		// 0, 1, 2, 3 for front, right, back, left
		if ((now.Y < 7) && (!checked_list[now.X][now.Y + 1]) && (Graph[now.X][now.Y][0] == 1)) {

			tmp.X = now.X;
			tmp.Y = now.Y + 1;
			q.push({ tmp,now });
			
		}
		if ((now.Y > 0) && (!checked_list[now.X][now.Y - 1]) && (Graph[now.X][now.Y][2] == 1)) {

			tmp.X = now.X;
			tmp.Y = now.Y - 1;
			q.push({ tmp,now });
			
		}
		if ((now.X < 7) && (!checked_list[now.X + 1][now.Y]) && (Graph[now.X][now.Y][3] == 1)) {

			tmp.X = now.X + 1;
			tmp.Y = now.Y;
			q.push({ tmp,now });
			
		}
		if ((now.X > 0) && (!checked_list[now.X - 1][now.Y]) && (Graph[now.X][now.Y][1] == 1)) {

			tmp.X = now.X - 1;
			tmp.Y = now.Y;
			q.push({ tmp,now });
			
		}
	}
	if (!checked_list[to.X][to.Y])
	{
		//不曾到达终点
		//前往最佳位置
		MainTask_MakePath(min_dist_pos);
		return 0;

	}

	if (checked_list[to.X][to.Y]) {
		//直接走到
		MainTask_MakePath(to);
		return 1;
	}



}

bool if_possibile = 0;
Pos MovePos(int dir) {
	Pos tmp = car.Position;
	if (dir == 0) {
		tmp.Y += 1;
	}
	else if (dir == 1) {
		tmp.X -= 1;
	}
	else if (dir == 2) {
		tmp.Y -= 1;
	}
	else if (dir == 3) {
		tmp.X += 1;
	}
	return tmp;
}
void UpdateCarOrient(int o) {
	if (o == 1) {
		car.Orientation += 1;
	}
	else if (o == 3) {
		car.Orientation -= 1;
	}
	car.Orientation += 4;
	car.Orientation %= 4;
}
void UpdateCarPos(Pos p) {
	car.Position = p;
}
void MainTask_GoPath()
{
	//0, 1, 2, 3 for front, right, back, left
	for (int i = 1; i <= pathlength; i++) {

		for (int j = 0; j <= 3; j++) {
			int dir = getPosition(j);
			if (MovePos(dir) == path[i]) {
				UpdateCarPos(path[i]);
				if (j == 0) {
					PL_GoStop();
				}
				else if (j == 2) {
					PL_GoBackStop();
				}
				else if (j == 1) {
					PL_CrossRoad(5);
					PL_GoStop();
					UpdateCarOrient(1);
				}
				else if (j == 3) {
					PL_CrossRoad(1);
					PL_GoStop();
					UpdateCarOrient(3);
				}

				
				break;
			}
		}

	}
}
void MainTask_Go(Pos from, Pos to)
{
	if (MainTask_SearchRoad(from, to))
	{
		//找到路
		MainTask_GoPath();
		return;
	}
	else
	{
		MainTask_GoPath();
		MainTask_ProbeObstacle();
		MainTask_Go(min_dist_pos, to);
	}
}

int MT_Pos2Node(int& x, int& y) {
	/*
	2,0: 106,15贴左边   85,15贴左开始拐（左轮刚过）78,24正好进入 81,14 开始拐（在入口中央）
	0,2:
*/

	if ((x >= 65 && x <= 80) && (y >= 17 && y <= 20)) {
		x = 2, y = 0;
	}

}

bool SavePeopleReadyforEntrance() {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());
	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}
bool SavePeopleBackReadytoGoBlind() {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());
	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}

bool SavePeopleReturnHome() {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());
	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}

void MainTask_GotoGoods() {
	while (!Manager_Time_TakeTime(12, 500))
	{
		PL_GoBlind(1);
	}
	Move_Stop();
	while (!MicroMove_IsPushed(1))
	{
		Motor_GoSpeed(0, 150);
	}

	Move_Stop();
	Motor_GoSpeed(150, 0);
	delay(150);
	while (!MicroMove_IsPushed(1))
	{
		Motor_GoSpeed(150, 150);
	}
	Motor_GoSpeed(100, -50);
	delay(600);
	while (!MicroMove_IsPushed(1))
	{
		Motor_GoSpeed(150, 150);
	}
	PL_GoBlind(1);
}

void MainTask_CollectGoods()
{
	MainTask_GotoGoods();
	//以下代码位于Pretest.cpp, 目前没有上位机
	GetballBack();
	/*while (true)
	{
		if (MicroMove_IsPushed(1)) { Motor_GoSpeed(150, -20); delay(50); }

		else Motor_GoSpeed(150, 155);
	}*/


}


void MainTask_GotoPeopleEntrance() {
	while (!Manager_Time_TakeTime(12, 500))
	{
		PL_GoBlind(2);
	}
	Move_Stop();
	while (!MicroMove_IsPushed(2))
	{
		Motor_GoSpeed(150, 0);
	}

	Move_Stop();
	Motor_GoSpeed(0, 150);
	delay(150);
	while (!MicroMove_IsPushed(2))
	{
		Motor_GoSpeed(150, 150);
	}
	Motor_GoSpeed(-50, 100);
	delay(600);
	while (!MicroMove_IsPushed(2))
	{
		Motor_GoSpeed(150, 150);
	}

	while (!SavePeopleReadyforEntrance()) {
		PL_GoBlind(1);
	}
	Move_Gotime(SPEED, SPEED, 300);
	PL_CrossRoad(1);
}

void MainTask_SavePeopleBackHome() {
	while (!MicroMove_IsPushed(2)) {
		Motor_GoSpeed(100, 0);
	}
	while (!SavePeopleBackReadytoGoBlind()) {
		PL_GoBlind(2);
	}
	Move_Gotime(SPEED, SPEED, 400);
	Move_Gotime(0, SPEED, 1000);
	while (!SavePeopleReturnHome()) {
		PL_GoBlind(2);
	}

}
void MainTask_SavePeople() {
	MainTask_GotoPeopleEntrance();
	int i = 1;
	while (i <= 3) {
		Pos org = { 5, 7 }, def = { 0, 2 };
		MainTask_Go(org, def);
		i++;
	}
	MainTask_SavePeopleBackHome();
}
