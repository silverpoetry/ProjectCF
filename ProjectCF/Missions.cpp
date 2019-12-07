#pragma once
#include "IncludeList.h"
#include "Missions.h"

void CollectGoods_GotoGoods () {

	//贴墙走出出发点
	Outer_GoPointByX (40, 2);
	delay (300);

	//以左轮为轴旋转至碰边
	Move_Gotime (0, 120, 900);
	delay(300);
	//Mpu_GoRelativeAngleAAA (-127);
	Move_Gotime (150,150, 800);
	delay(300);
	Move_Gotime (120, 0, 400);
	delay(300);
	//Mpu_GoRelativeAngleAAA (25);

	//至此来到下面的路上


}
void CollectGoods_CatchBall () {
	//delay (300);
	Move_Gotime (120, 0, 1000);
	delay(300);
//	Mpu_GoRelativeAngleAAA (133);
	Move_Gotime (-100,-100, 700);
	delay (300);
}
void CollectGoods_GetballBack () {
	Move_Gotime (120, 0, 430);
	delay(300);
	//Mpu_GoRelativeAngleAAA (39);
	Outer_GoPointByY (75, 2);
	delay(300);

	Move_Gotime(0, 120, 650);
	delay(300);

	MainTask_EasyMaze ();

	return;
}
void MainTask_CollectGoods ()
{
	while (1) {
		while (!Zigbee_MessageRecord ());
		if (Game.GameState == GameGoing) {
			break;
		}
	}
	CollectGoods_GotoGoods ();
	Outer_GoPointByY (41, 1);
	Move_Stop ();
	delay(500);
	CollectGoods_CatchBall ();
	CollectGoods_GetballBack ();
	Move_Gotime (0, 120, 700);
	delay(300);
//	Mpu_GoRelativeAngleAAA (-85);
	MainTask_EasyMaze ();
}
//}
//}

void EasyMaze_ReturnHome () {
	//!!!!!
	//Mpu_GoRelativeAngleAAA (-85);
	Move_Gotime(0, 120, 600);
	delay(300);
	Outer_GoPointByX (Ms_Pos_E, 1);
	delay(300);

	//!!!!
	//Mpu_GoRelativeAngleAAA (170);
	Move_Gotime(120,0, 1300);
	delay(300);


	Outer_GoPointByX (Ms_Pos_F, 1);
	//delay(300);
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
//	Mpu_RecordAngle ();
	while (!Huidu_IsCrossRoad ()) {
		Move_GoSpeed (150, 150);
	
	//	if (!Manager_Time_TakeTime (69, 100))
		//{
			//Mpu_ReadData();
		//	Mpu_AdjustStraight (SPEED);

		//}
	}
	Move_Gotime (150,150,  80);
	Move_Stop ();

	//PL_GoStop ();

	GridHelper_Go (car.Position, exit);
	gh_exit ({ 2,0 });

	EasyMaze_ReturnHome ();
	Move_Stop();
}



void SavePeople_GotoEntrance () {
	/*	while (1) {
			while (!Zigbee_MessageRecord);
			if (Game.GameState == GameGoing) {
				break;
			}
		}
	*/

		while (!Manager_Time_TakeTime(45,1000))
		{
			
				if (MicroMove_IsPushed(2))Motor_GoSpeed(140, 160);
				else Motor_GoSpeed(170, 130);
		}
		while (!Manager_Time_TakeTime(45, 200))
		{

			Move_GoSpeed(60, 120);
		}
		
		/*Move_Gotime (150, -150, 300);
		Move_Gotime (150, 150, 300);
		Move_Gotime (-150, 150, 300);*/
	
	Outer_GoPointByY (152, 2);
	delay(300);
	Move_Gotime (150,150, 300);
	delay(300);
	Move_Gotime(120, 0, 700);
	//Mpu_GoRelativeAngleAAA (85);
}

void MainTask_SavePeople () {
	
	//while

	SavePeople_GotoEntrance ();
	while (1) {
		//	while (!Zigbee_MessageRecord ());
			//if (Game.GameState == GameGoing) {
				//SavePeople_GotoEntrance ();
			//	PreContest_SavePeople ();
			//}
	}
}