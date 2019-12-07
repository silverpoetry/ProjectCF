#include "PreContest.h"
#include "IncludeList.h"



void PreContest_GoStraight (int opt) {
	if (opt == 1) { 
		Outer_GoPointByX (Ms_Pos_E, 2);
	}
	else if (opt == 2) {
		Outer_GoPointByY (Ms_Pos_I, 2);
	}
	Move_Stop ();
	delay (500);
	return;
}

void PreContest_ReceiveSignal () {
	while (1) {
		while (!Zigbee_MessageRecord ());
		if (Game.GameState == 1) {
			PL_GoBlind (2);
		}
		if (Game.GameState == 2) {
			Move_Stop ();
		}
		if (Game.GameState == 3) {
			break;
		}
	}
	return;
}
void PreContest_OuterRoadMove () {
	CollectGoods_GotoGoods ();
	Outer_GoPointByY (Ms_Pos_L, 1);
	Move_Stop ();
	return;
}
void PreContest_CollectGoods () {
	CollectGoods_GotoGoods();
	Outer_GoPointByY(Ms_Pos_L, 1);
	Move_Stop();
	Arm_Go(2, 50);
	delay(500);
	Outer_GoPointByY (Ms_Pos_A, 1);
	Move_Stop ();
	delay (500);
	CollectGoods_CatchBall ();
	Outer_GoPointByY (Ms_Pos_G, 3);
	Move_Stop ();
	CollectGoods_DropBall ();
	//CollectGoods_GetballBack ();
}
void PreContest_EasyMaze () {
	GridHelper_Init();
	car.Position = { 6, 5 };
	Pos exit = { 2, 1 };
	car.Orientation = 1;
	PL_GoStop();
	
	GridHelper_Go (car.Position, exit);
	gh_exit({ 2,0 });
	
	
}
void PreContest_SavePeople () {
	SavePeople_GotoEntrance ();
	//Mpu_RecordAngle ();
	while (!Huidu_IsCrossRoad ()) {
		Move_GoSpeed(130, 130);
	//	if (!Manager_Time_TakeTime (70, 100))
		//{
			//Mpu_ReadData();
			//Mpu_AdjustStraight (SPEED);

		//}
	}
	Move_GoStraightTime (150, 80);


	//PL_GoStop ();
	int i = 1;
	//直接全图视野
	GridHelper_Init();
	car.Position = { 1, 2 };
	Pos exit = { 5, 2 };
	car.Orientation = 3;

	while (Manager_Time_TakeTime (35, 500))Zigbee_MessageRecord ();


	while (true) {
		while (Manager_Time_TakeTime(35,1000))Zigbee_MessageRecord();

		
		if (Game.GameState == GameOver) {
			Move_Stop ();
			return;
		}

		Pos person1 = GridHelper_PositionConverter ({ Passenger[0].pos.X ,Passenger[0].pos.Y }), person2 = GridHelper_PositionConverter ({ Passenger[1].pos.X ,Passenger[1].pos.Y });
		if (isposeq(person1, car.Position))person1 = person2;
		if (isposeq(person2, car.Position))person2 = person1;
		if (GridHelper_CntManhattonDist (car.Position, person1) < GridHelper_CntManhattonDist (car.Position, person2)) {
			 GridHelper_Go (car.Position, person1);
		}
		else {
			 GridHelper_Go (car.Position, person2);
		}
		i++;
	}
/*
	GridHelper_Go (car.Position, exit);
	gh_exit({ 0,2 });
	Move_Stop ();*/
}
void Precontest_GoPlace()
{
	CollectGoods_GotoGoods();
	Outer_GoPointByY(150, 1);
	Move_Stop();
}

void shadiao_shabi (void) {
	int i = 0;
	while (i++ <= 30) {
		Mpu_GoRelativeAngleAAA (-83);
	}
//	PL_GoCrossTurnLeft ();
}

void lianxun (void) {
	int i = 0;
	while (i++ < 30) {
		Mpu_GoRelativeAngleAAA (-83);
	}
	}


/*	int i = 0;
//	while (i < 3) {
	//	Move_Gotime (160, 140, 400);
		PL_GoBlind (2);
		delay (600);
		Mpu_GoRelativeAngleAAA (-125);
		Move_GoStraightTime (150, 800);
		Mpu_GoRelativeAngleAAA (25);

		PL_GoBlind (1);
		delay (2000);
		Move_Stop ();

		CollectGoods_CatchBall ();
		Mpu_GoRelativeAngleAAA (40);
		PL_GoBlind (2);
		delay (500);

		Move_Stop ();
		delay (5000);

		Mpu_GoRelativeAngleAAA (-80);
		PL_GoBlind (1);
		delay (600);

		Mpu_GoRelativeAngleAAA (170);
		PL_GoBlind (1);
		delay (1500);
	
		Move_Stop ();
		delay (500);


		//MatinTask_EasyMaze();
*/
		
//	}

