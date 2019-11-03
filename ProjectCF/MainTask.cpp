#include "MainTask.h"

int MT_GraphInit () {

	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			for (int k = 1; k <= 4; k++) {
				Graph[i][j][k] = 1;
			}
		}
	}


}

int MT_FindExit (int x, int y) {
	if ((x == 2 && y == 0) || (x == 5 && y == 7)) {
		ExploreMaze (1);
	}
	else if ((x == 0 && y == 2) || (x == 7 && y == 5)) {
		ExploreMaze (2);
	}

}

int MT_FindEntrance (int road) {
	while (1) {
		if (Zigbee_MessageRecord ()) {
			int x = Car[0].pos.X, y = Car[0].pos.Y;
			Move_GoSpeed (SPEED, SPEED);
			if (x <= 82) {
				Move_Stop ();
				delay (500);
				while (1) {
					if (Manager_Time_TakeTime (30, 30)) {
						Move_TurnLeft (150);
						if (Huidu_IsLine (2)) {
							Move_Stop ();
							delay (500);
							return;
						}
					}
				}

			}
			//MT_Pos2Node (x, y);
		}
	}
	//MT_FindExit (2, 0);
}

int MT_Pos2Node (int& x, int& y) {
	/*
	2,0: 106,15贴左边   85,15贴左开始拐（左轮刚过）78,24正好进入 81,14 开始拐（在入口中央）
	0,2:
	*/

	if ((x >= 65 && x <= 80) && (y >= 17 && y <= 20)) {
		x = 2, y = 0;
	}

}
int MT_FreeMaze (void) {
	int x = Car[0].pos.X, y = Car[0].pos.Y;
	if (Zigbee_MessageRecord ()) {
		MT_Pos2Node (x, y);
	}
}

int MT_Main () {
	MT_FindEntrance (1);
	MT_FindExit (2, 0);
	return 1;
}