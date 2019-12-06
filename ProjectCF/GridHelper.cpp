#include "GridHelper.h"
#include "IncludeList.h"
int Graph[8][8][6];
//0, 1, 2, 3 for front, right, back, left
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

	if (val==-1)
	{

		if (pos == 0) Debugger_Print("stob", car.Position.X, car.Position.Y + step, pos);
		if (pos == 1)Debugger_Print("stob", car.Position.X - step,car.Position.Y,pos);
		if (pos == 2)Debugger_Print("stob", car.Position.X, car.Position.Y - step, pos);
		if (pos == 3) Debugger_Print("stob", car.Position.X + step, car.Position.Y, pos);
	}
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

Pos GridHelper_PositionConverter(Pos p)
{
	Pos startpoint = { 52,52 };
	int blockwidth = 30;
	p.X -= startpoint.X;
	p.Y -= startpoint.Y;
	Pos ret;
	p.X = (int)(((float)(p.X)) / blockwidth + 0.5) + 1;
	p.Y = (int)(((float)(p.Y)) / blockwidth + 0.5) + 1;
	ret.Y = 7-p.Y;
	ret.X = 7 - p.X;
	return ret;


}
int GridHelper_CntManhattonDist(Pos from, Pos to) {
	return abs(from.X - to.X) + abs(from.Y - to.Y);
}



void GridHelper_InitGraph() {

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
void GridHelper_Init()
{
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			Graph[i][j][0] = Graph[i][j][1] = Graph[i][j][2] = Graph[i][j][3] = 0;
		}
	}
	GridHelper_InitGraph();

}
void GridHelper_Init2()
{
	for (int i = 0; i <= 7; i++) {
		for (int j = 0; j <= 7; j++) {
			Graph[i][j][0] = Graph[i][j][1] = Graph[i][j][2] = Graph[i][j][3] = 1;
		}
	}

	GridHelper_InitGraph();

	Graph[1][4][0] = -1;
	Graph[1][5][2] = -1;
	Graph[1][5][3] = -1;
	Graph[2][4][3] = -1;
	Graph[2][5][1] = -1;
	Graph[3][3][0] = -1;
	Graph[3][4][0] = -1;
	Graph[3][4][1] = -1;
	Graph[3][4][2] = -1;
	Graph[3][5][2] = -1;

}


//获取障碍物距离
int GridHelper_GetDistanceLevel(int dir)
{
	int dis = Distance_Get(map_sensor[dir]);
	if (obstacle_range[dir][0][0] < dis&&dis < obstacle_range[dir][0][1])
	{
		//近在眼前
		return 1;
	}
	else if (obstacle_range[dir][1][0] < dis&&dis < obstacle_range[dir][1][1])
	{
		return 2;
	}
	else
	{
		return 3;
	}
}
//侦查障碍物
void GridHelper_Detect()
{

	//k代表方向的循环
	for (int k = 0; k <= 3; k++)
	{
		//后面不用探测
		if (k == 2)continue;
		int dislevel = GridHelper_GetDistanceLevel(k);
		//n代表距离的循环
		for (int n = 1; n <= 2; n++)
		{

			//已探测直接滚蛋
			if (GetVal(k, n - 1) != 0)break;

			if (n < dislevel)SetVal(k, n - 1, 1);
			else
			{
				SetDisabled(k, n - 1);
				break;
			}


		}
	}


}


//寻路模块
Pos path[100]; int pathlength = 0;
Pos link_last[9][9];
int maplength[9][9];
Pos min_dist_pos = { 1, 1 };
int min_dist = 1000;
void UpdateMinDistPos(Pos tmp, Pos to) {
	//内部路线长度权值1
	int length = GridHelper_CntManhattonDist(tmp, to) + maplength[tmp.X][tmp.Y];
	if (length < min_dist) {
		min_dist_pos = tmp;
		min_dist = length;
	}
}
void GridHelper_MakePath(Pos p)
{
	pathlength = maplength[p.X][p.Y];

	Dwn(i, pathlength, 1)
	{
		path[i] = p;
		p = link_last[p.X][p.Y];
	}
}
bool GridHelper_SearchRoad(Pos from, Pos to) {
	
	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			checked_list[i][j] = 0, link_last[i][j] = { i,j }, maplength[i][j] = 0;
	pathlength = 0;

	min_dist_pos = { 1,1 };
	min_dist = 1000;
	/*Serial.println(from.X);
	Serial.println(from.Y);	*/
	Queue<queueitem> q;
	q.push({ from,from });
	

	while (!q.empty()) {
		
		Pos now = q.front().to;
		Pos last = q.front().from;
		/*Serial.println(now.X);
		Serial.println(now.Y);*/
		
		if (checked_list[now.X][now.Y]) { q.pop();  continue; }
		
		
		checked_list[now.X][now.Y] = 1;
		
		//记录来路
		link_last[now.X][now.Y].X = last.X;
		link_last[now.X][now.Y].Y = last.Y ;
		maplength[now.X][now.Y] = maplength[last.X][last.Y] + 1;
		
		q.pop();
		
		
		//如果存在未探索点，将其加入搜索
		bool b = false;
		for (int i = 0; i <= 3; i++)b = (b || (Graph[now.X][now.Y][i] == 0));
		if (b)UpdateMinDistPos(now, to);
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
		GridHelper_MakePath(min_dist_pos);
		return 0;

	}

	if (checked_list[to.X][to.Y]) {
		//直接走到
		GridHelper_MakePath(to);
		return 1;
	}



}
//如果已经发现的路一定是最短则走，否则进行探险（走到最优的未探索点）
bool GridHelper_SearchRoadAdventure(Pos from, Pos to) {

	for (int i = 0; i <= 7; i++)
		for (int j = 0; j <= 7; j++)
			checked_list[i][j] = 0, link_last[i][j] = { i,j }, maplength[i][j] = 0;
	pathlength = 0;

	min_dist_pos = { 1,1 };
	min_dist = 1000;
	/*Serial.println(from.X);
	Serial.println(from.Y);	*/
	Queue<queueitem> q;
	q.push({ from,from });


	while (!q.empty()) {

		Pos now = q.front().to;
		Pos last = q.front().from;
		/*Serial.println(now.X);
		Serial.println(now.Y);*/

		if (checked_list[now.X][now.Y]) { q.pop();  continue; }


		checked_list[now.X][now.Y] = 1;

		//记录来路
		link_last[now.X][now.Y].X = last.X;
		link_last[now.X][now.Y].Y = last.Y;
		maplength[now.X][now.Y] = maplength[last.X][last.Y] + 1;

		q.pop();


		//如果存在未探索点，将其加入搜索
		bool b = false;
		for (int i = 0; i <= 3; i++)b = (b || (Graph[now.X][now.Y][i] == 0));
		if (b)UpdateMinDistPos(now, to);
		//找到
		if (now.X == to.X && now.Y == to.Y)
		{
			int length = GridHelper_CntManhattonDist(now, to) + maplength[now.X][now.Y];
			if (length <= min_dist)
			{
				min_dist_pos = now;
				min_dist = length;
			}
			break;
		}

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
	if (isposeq(min_dist_pos,to))
	{
		//可以到达终点且最优
		GridHelper_MakePath(min_dist_pos);
		return true;

	}
	else
	{
		GridHelper_MakePath(min_dist_pos);
		return false;
	}

	



}


void UpdateCarOrient(int o) {
	if (o == 1) {
		car.Orientation += 1;
	}
	else if (o == 3) {
		car.Orientation -= 1;
	}
	else if(o==4)
	{
		car.Orientation += 2;
	}
	car.Orientation += 4;
	car.Orientation %= 4;
}
void UpdateCarPos(Pos p) {
	car.Position = p;
}
void GridHelper_GoPath()
{
	//Debugger_SetWatch("PLEN", pathlength);
	//0, 1, 2, 3 for front, right, back, left
	for (int i = 1; i <= pathlength; i++) {
		for (int j = 0; j <= 3; j++) {

	/*Debugger_SetWatch ("posx", car.Position.X);
	Debugger_SetWatch ("posy", car.Position.Y);*/
			Debugger_Print("stpos", car.Position.X, car.Position.Y,1);

			int dir = getPosition(j);
			if (isposeq(MovePos(dir), path[i])) {
	//		Serial.print(path[i].X), Serial.print(","), Serial.print(path[i].Y), Serial.print("\n");

				//Serial.println(i);
				//delay(150);
				UpdateCarPos(path[i]);
				if (j == 0) {
					
					PL_GoWithoutStop();
					
			//		Debugger_SetWatch("Action", "Forward");
				}
				else if (j == 2) {
					
					Move_GoSpeed(150, -150);
					
					delay(260);
					PL_CrossRoad(5);
					PL_GoWithoutStop ();
					UpdateCarOrient(4);
				//	Debugger_SetWatch("Action", "Back");
				}
				else if (j == 1) {

					
					Move_Stop();
					PL_CrossRoad(5);
					PL_GoWithoutStop ();
					UpdateCarOrient(1);
				//	Debugger_SetWatch("Action", "RT");
				}
				else if (j == 3) {
					//	Move_GotimeWithoutStop(150, 50);
					Debugger_SetWatch("Action", "LT");
					
					Move_Stop();
					PL_CrossRoad(1);
					PL_GoWithoutStop ();
					UpdateCarOrient(3);
				}
				Move_Gotime(150, 150, 50);

				break;
			}
		}

	}
	Move_Stop();
}

void gh_exit(Pos p)
{
	for (int j = 0; j <= 3; j++) {

		int dir = getPosition(j);
		if (isposeq(MovePos(dir),p)) {
			//		Serial.print(path[i].X), Serial.print(","), Serial.print(path[i].Y), Serial.print("\n");

						//Serial.println(i);
			//delay(300);
			
			if (j == 0) {
				Move_GoStraightTime(150, 500);

				//		Debugger_SetWatch("Action", "Forward");
			}
			else if (j == 2) {
				Move_Gotime (150, 150, 140);
				Move_GoSpeed (150, -150);

				delay (260);
				PL_CrossRoad (5);
				Move_GoStraightTime(150, 400);
				//	Debugger_SetWatch("Action", "Back");
			}
			else if (j == 1) {

				PL_GoLineTime(200);
				//Move_Stop();
				Mpu_GoRelativeAngle(79);
				//Move_Stop();
				Move_GoStraightTime(150, 500);
				//	Debugger_SetWatch("Action", "RT");
			}
			else if (j == 3) {
				//	Move_GotimeWithoutStop(150, 50);
				Move_Gotime (150, 150, 140);
				Move_GoSpeed (-150, 150);

				delay (260);
				PL_CrossRoad (5);
				//Move_Stop();
				Move_GoStraightTime(150, 500);
			}


			break;
		}
	}
	Move_Stop ();
	
}

void GridHelper_Go(Pos from, Pos to)
{
	GridHelper_Detect();

	if (GridHelper_SearchRoad(from, to))
	{
		
		//找到路
		GridHelper_GoPath();
		return;
	}
	else
	{
		GridHelper_GoPath();
		GridHelper_Detect();
		GridHelper_Go(min_dist_pos, to);
	}
}
void GridHelper_GoAdventure(Pos from, Pos to)
{
	GridHelper_Detect();
	if (GridHelper_SearchRoadAdventure(from, to))
	{

		//找到路
		GridHelper_GoPath();
		return;
	}
	else
	{
		GridHelper_GoPath();
		GridHelper_Detect();
		GridHelper_Go(min_dist_pos, to);
	}
}
