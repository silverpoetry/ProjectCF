#pragma once
#include "IncludeList.h"
#include "Missions.h"

void CollectGoods_GotoGoods () {

	//��ǽ�߳�������
	Outer_GoPointByX (AAA, 2);

	//������Ϊ����ת������
	Mpu_GoRelativeAngleAAA (-125);
	Move_GoStraightTime (150, 800);
	Mpu_GoRelativeAngleAAA (25);

	//�������������·��
	
	
}
void CollectGoods_CatchBall () {
	Mpu_GoRelativeAngleAAA (130);
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
	while (1) {
		while (!Zigbee_MessageRecord ());
		if (Game.GameState == GameGoing) {
			CollectGoods_GotoGoods ();
			Outer_GoPointByY (Ms_Pos_A, 1);
			Move_Stop ();
			CollectGoods_CatchBall ();
			CollectGoods_GetballBack ();
			Mpu_GoRelativeAngleAAA (-80);
			MainTask_EasyMaze ();
		}
	}
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

	//�ӳ�����ǰ���Թ����
	Mpu_GoRelativeAngleAAA (-80);
	Move_GoStraightTime (150, 500);
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
	Outer_GoPointByY (150, 1);
	Move_GoStraightTime (150, 300);
	Mpu_GoRelativeAngleAAA (80);
}

void MainTask_SavePeople() {

	while (1) {
		while (!Zigbee_MessageRecord ());
		if (Game.GameState == GameGoing) {
			SavePeople_GotoEntrance ();
			PreContest_SavePeople ();
		}
	}
}