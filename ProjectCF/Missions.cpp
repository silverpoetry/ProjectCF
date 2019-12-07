#pragma once
#include "IncludeList.h"
#include "Missions.h"

void CollectGoods_GotoGoods () {

	//贴墙走出出发点
	Outer_GoPointByX (37, 2);
	delay (300);

	//以左轮为轴旋转至碰边
	Mpu_GoRelativeAngleAAA (-127);
	Move_GoStraightTime (150, 800);
	Mpu_GoRelativeAngleAAA (25);

	//至此来到下面的路上


}
void CollectGoods_CatchBall () {
	//delay (300);

	Mpu_GoRelativeAngleAAA (133);
	Move_GoStraightTime (-150, 550);
	delay (300);
}
void CollectGoods_GetballBack () {
	Mpu_GoRelativeAngleAAA (39);
	Outer_GoPointByY (78, 2);
	MainTask_EasyMaze ();

	return;
}
void MainTask_CollectGoods ()
{/*
	while (1) {
		while (!Zigbee_MessageRecord ());
		if (Game.GameState == GameGoing) {
			break;
		}
	}*/
	CollectGoods_GotoGoods ();
	Outer_GoPointByY (40, 1);
	Move_Stop ();
	CollectGoods_CatchBall ();
	CollectGoods_GetballBack ();
	Mpu_GoRelativeAngleAAA (-85);
	MainTask_EasyMaze ();
}
//}
//}

void EasyMaze_ReturnHome () {
	//!!!!!
	Mpu_GoRelativeAngleAAA (-85);
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
//	Move_GoStraightTime (150, 500);
	GridHelper_Init ();
	car.Position = { 6, 5 };
	Pos exit = { 2, 1 };
	car.Orientation = 1;
	Mpu_RecordAngle ();
	while (!Huidu_IsCrossRoad ()) {
	
	//	if (!Manager_Time_TakeTime (69, 100))
		//{
			//Mpu_ReadData();
			Mpu_AdjustStraight (SPEED);

		//}
	}
	Move_GoStraightTime (150, 80);
//	Move_Stop ();

	//PL_GoStop ();

	GridHelper_Go (car.Position, exit);
	gh_exit ({ 2,0 });

	EasyMaze_ReturnHome ();
}



void SavePeople_GotoEntrance () {
	/*	while (1) {
			while (!Zigbee_MessageRecord);
			if (Game.GameState == GameGoing) {
				break;
			}
		}
	*/

	/*	while (!Manager_Time_TakeTime(45,500))
		{
			PL_GoBlind (2);
		}
		Move_Gotime (150, -150, 300);
		Move_Gotime (150, 150, 300);
		Move_Gotime (-150, 150, 300);
	*/
	Outer_GoPointByY (150, 2);
	Move_GoStraightTime (150, 300);
	Mpu_GoRelativeAngleAAA (85);
}

void MainTask_SavePeople () {

	SavePeople_GotoEntrance ();
	while (1) {
		//	while (!Zigbee_MessageRecord ());
			//if (Game.GameState == GameGoing) {
				//SavePeople_GotoEntrance ();
			//	PreContest_SavePeople ();
			//}
	}
}