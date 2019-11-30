#pragma once
#include "IncludeList.h"
#include "Missions.h"

void CollectGoods_GotoGoods () {
	//!!!!!

	//贴墙走出出发点
	Outer_GoPointByX (AAA, 2);

	//以左轮为轴旋转至碰边
	Mpu_GoRelativeAngleAAA (-125);
	Move_GoStraightTime (150, 800);
	Mpu_GoRelativeAngleAAA (25);

	//至此来到下面的路上
	
	
}
void CollectGoods_CatchBall () {
	Mpu_GoRelativeAngleAAA (145);
	Move_GoStraightTime (-150, 550);
	delay (300);
}
void CollectGoods_GetballBack () {
	Mpu_GoRelativeAngleAAA (40);
	Outer_GoPointByY (Ms_Pos_B, 2);
	MainTask_EasyMaze ();

	return;
}
void MainTask_CollectGoods()
{
	CollectGoods_GotoGoods();
	Outer_GoPointByY(Ms_Pos_A,1);
	Move_Stop();
	CollectGoods_CatchBall();
	CollectGoods_GetballBack();
	Mpu_GoRelativeAngleAAA (-80);
	MainTask_EasyMaze ();
}

void EasyMaze_ReturnHome () {
	//!!!!!
	Mpu_GoRelativeAngleAAA (-80);
	Outer_GoPointByX (Ms_Pos_E, 1);


	//!!!!
	Mpu_GoRelativeAngleAAA (170);
	Outer_GoPointByX (Ms_Pos_F, 1);
	Move_Stop ();
	delay (500);
	return;
}

void MainTask_EasyMaze () {

	//从出发点前往迷宫入口

	Move_GoStraightTime (150, 400);
	GridHelper_Init ();
	car.Position = { 6, 5 };
	Pos exit = { 2, 1 };
	car.Orientation = 1;
	PL_GoStop ();

	GridHelper_Go (car.Position, exit);
	gh_exit ({ 2,0 });

	EasyMaze_ReturnHome ();
}



void SavePeople_GotoEntrance() {
/*
	//拐左上大弯
	//!!!!!
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
	
	Outer_GoStraightPointByX( Ms_Pos_H);
	return;*/
}

void SavePeople_BackHome() {
	
	//!!!!!
	while (!MicroMove_IsPushed(2)) {
		Motor_GoSpeed(100, 0);
	}
	Outer_GoPointByY (Ms_Pos_I, 2);

	//!!!!!
	Move_Gotime(0, SPEED, 1000);
	Outer_GoPointByY (Ms_Pos_J, 2);
	Move_Stop ();
	delay (500);
	return;
}

void MainTask_SavePeople() {

	SavePeople_GotoEntrance ();
	PL_CrossRoad (1);

	PreContest_SavePeople ();

/*
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

	GridHelper_Go(car.Position, exit);*/
	SavePeople_BackHome ();
}