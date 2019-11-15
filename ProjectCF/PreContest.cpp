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
	car.Position = { 0, 5 };
	Pos exit = { 5, 0 };
	car.Orientation = 3;
	GridHelper_Go (car.Position, exit);
	Move_Stop ();
}
void PreContest_SavePeople () {
	int i = 1;
	car.Position = { 7, 2 };
	Pos exit = { 2, 7 };
	car.Orientation = 1;

	while (i <= 3) {
		while (!Zigbee_MessageRecord ());
		Pos person1 = GridHelper_PositionConverter ({ Passenger[0].pos.X ,Passenger[0].pos.Y }), person2 = GridHelper_PositionConverter ({ Passenger[1].pos.X ,Passenger[1].pos.Y });

		if (GridHelper_CntManhattonDist (car.Position, person1) < GridHelper_CntManhattonDist (car.Position, person2)) {
			GridHelper_Go (car.Position, person1);
		}
		else {
			GridHelper_Go (car.Position, person2);
		}
		i++;
	}

	GridHelper_Go (car.Position, exit);
	Move_Stop ();
}
