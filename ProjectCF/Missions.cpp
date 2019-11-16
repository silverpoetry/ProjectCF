#pragma once
#include "IncludeList.h"
#include "Missions.h"

void CollectGoods_GotoGoods () {
	//!!!!!

	//贴墙走出出发点
	while (!Manager_Time_TakeTime (12, 500))
		PL_GoBlind (2);
	Move_Stop ();

	//以左轮为轴旋转至碰边
	while (!MicroMove_IsPushed (1))
		Motor_GoSpeed (0, 150);
	Move_Stop ();

	//反向微调
	Motor_GoSpeed (150, 0); delay (150);

	//再次前进至边
	while (!MicroMove_IsPushed (1))
		Motor_GoSpeed (150, 150);

	//继续反向调整
	Motor_GoSpeed (100, -50);
	delay (600);

	//前进至再次到边界
	while (!MicroMove_IsPushed (1))
		Motor_GoSpeed (150, 150);

	//至此来到下面的路上
	//PL_GoBlind (1);

}
void CollectGoods_CatchBall () {
	//!!!!!
	Arm_PickBall ();
}
void CollectGoods_GetballBack () {
	Outer_GoPointByY (Ms_Pos_B, 3);

	//拐左下大弯
	while (!Manager_Time_TakeTime (50, 200)) {
		Move_GoSpeed (150, 150);
	}
	Move_Stop ();
	Motor_GoSpeed (-225, -80);
	delay (1400);
	Move_Stop ();

	//躲右下迷宫入口
	Outer_GoPointByX (Ms_Pos_C, 4);
	Outer_GoPointByXWithoutMicroMove (Ms_Pos_D, -1);
	
	Outer_GoPointByX (Ms_Pos_E, 4);

	//!!!!!
	while (!Manager_Time_TakeTime (51, 1000)) {
		Motor_GoSpeed (0, -150);
	}
	Outer_GoPointByX (Ms_Pos_F, 4);
	Move_Stop ();
	delay (500);
	return;
}
void CollectGoods_DropBall () {
	//!!!!!
	Arm_DropBall ();
}
void MainTask_CollectGoods()
{
	CollectGoods_GotoGoods();
	Outer_GoPointByY(Ms_Pos_A,1);
	Move_Stop();
	CollectGoods_CatchBall();
	CollectGoods_GetballBack();
	CollectGoods_DropBall ();
}


//0 front, 1 right, 2 back, 3 left
void EasyMaze_GoEntrance () {
	//从出发点前往迷宫入口

	//拐左下大弯
	CollectGoods_GotoGoods ();
	Outer_GoPointByY (Ms_Pos_G, 1);
}
void EasyMaze_ReturnHome () {
	//!!!!!
	while (!MicroMove_IsPushed (1)) {
		Motor_GoSpeed (0, 100);
	}

	Outer_GoPointByX (Ms_Pos_E, 1);
	Outer_GoPointByXWithoutMicroMove (Ms_Pos_K, 1);

	//!!!!!
	while (!Manager_Time_TakeTime (52, 2000)) {
		Motor_GoSpeed (100, 0);
	}

	Outer_GoPointByX (Ms_Pos_F, 1);
	Move_Stop ();
	delay (500);
	return;
}

void MainTask_EasyMaze () {

	//从出发点前往迷宫入口
	EasyMaze_GoEntrance ();
	PL_CrossRoad (5);

	car.Position = { 0, 5 };
	Pos exit = { 5, 0 };
	car.Orientation = 3;
	GridHelper_Go (car.Position, exit);
	EasyMaze_ReturnHome ();
}



void SavePeople_GotoEntrance() {

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
	
	Outer_GoPointByXWithoutMicroMove (Ms_Pos_H, 1);
	return;
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
	SavePeople_BackHome ();
}