#include "IncludeList.h"


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

	//初始位置
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



bool EasyMazeReadyforEntrance() {

	const int standard_x = 185, standard_y = 0;

	const int eps_x = 2, eps_y = 5;

	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.X - standard_x) < eps_x) {

		return 1;

	}

}

bool EasyMazeReadyforTurnRight() {

	const int standard_x = 185, standard_y = 0;

	const int eps_x = 2, eps_y = 5;

	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.X - standard_x) < eps_x) {

		return 1;

	}

}

bool EasyMazeGetHome() {

	const int standard_x = 185, standard_y = 0;

	const int eps_x = 2, eps_y = 5;

	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.X - standard_x) < eps_x) {

		return 1;

	}

}



bool GetballReadytoCatch() {

	const int standard_x = 185, standard_y = 0;

	const int eps_x = 2, eps_y = 5;

	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.X - standard_x) < eps_x) {

		return 1;

	}

}



void MainTask_GotoGoods() {
	//物资运输

	//贴墙走出出发点
	while (!Manager_Time_TakeTime(12, 500))
		PL_GoBlind(2);

	Move_Stop();

	//以左轮为轴旋转至碰边
	while (!MicroMove_IsPushed(1))
		Motor_GoSpeed(0, 150);
	Move_Stop();

	//反向微调
	Motor_GoSpeed(150, 0);delay(150);

	//再次前进至边
	while (!MicroMove_IsPushed(1))
		Motor_GoSpeed(150, 150);

	//继续反向调整
	Motor_GoSpeed(100, -50);
	delay(600);

	//前进至再次到边界
	while (!MicroMove_IsPushed(1))
		Motor_GoSpeed(150, 150);
	
	//至此来到下面的路上
	//PL_GoBlind (1);

}

void MainTask_CatchBall();

#include "Missions.h"
#include "IncludeList.h"
void MainTask_CollectGoods()

{

	MainTask_GotoGoods();
	
	Outer_GoPintByY(Ms_Pos_A,1);

	

	Move_Stop();

	MainTask_CatchBall();

	GetballBack();

}



void MainTask_GotoPeopleEntrance() {

	while (!Manager_Time_TakeTime(12, 500))

	{

		PL_GoBlind(1);

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



void EasyMazeGoEntrance() {
	//从出发点前往迷宫入口

	//先进行物资运输
	MainTask_GotoGoods();

	while (!EasyMazeReadyforEntrance()) {

		PL_GoBlind(2);

	}

	Move_Gotime(SPEED, SPEED, 400);

	PL_CrossRoad(2);



	/*

	while (!Manager_Time_TakeTime (12, 500))

	{

		PL_GoBlind (1);

	}

	Move_Stop ();

	Move_Gotime (0, 100, 500);

	Move_Gotime (100, 0, 500);

	while (!EasyMazeReadyforEntrance ()) {

		PL_GoBlind (1);

	}

	Move_Gotime (SPEED, SPEED, 300);

	PL_CrossRoad (1);*/

}

void EasyMazeReturnHome() {

	while (!MicroMove_IsPushed(1)) {

		Motor_GoSpeed(0, 100);

	}

	Move_Stop();

	while (!EasyMazeReadyforTurnRight()) {

		Motor_GoSpeed(100, 100);

	}

	Move_Gotime(120, 0, 2000);

	while (!EasyMazeGetHome()) {

		PL_GoBlind(2);

	}

	return;

}





void MainTask_EasyExploreMaze() {

	//从出发点前往迷宫入口
	EasyMazeGoEntrance();

	car.Position = { 0, 5 };

	Pos exit = { 5, 0 };

	car.Orientation = 3;

	GridHelper_Go(car.Position, exit);

	EasyMazeReturnHome();



}

void MainTask_SavePeople() {

	MainTask_GotoPeopleEntrance();

	int i = 1;



	car.Position = { 7, 2 };

	Pos exit = { 2, 7 };

	car.Orientation = 1;

	while (i <= 3) {

		while (!Zigbee_MessageRecord());

		Pos person1 = GridHelper_PositionConverter({ Passenger[0].pos.X ,Passenger[0].pos.Y }), person2 = GridHelper_PositionConverter({ Passenger[1].pos.X ,Passenger[1].pos.Y });

		if (GridHelper_CntManhattonDist(car.Position, person1) < GridHelper_CntManhattonDist(car.Position, person2)) {

			GridHelper_Go(car.Position, person1);

		}

		else {

			GridHelper_Go(car.Position, person2);

		}

		i++;

	}

	GridHelper_Go(car.Position, exit);

	MainTask_SavePeopleBackHome();

}

bool isposeq(Pos p1, Pos p2)
{
	return p1.X == p2.X&&p1.Y == p2.Y;
}