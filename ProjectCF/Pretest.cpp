#pragma once
#include "IncludeList.h"

int ExploreMaze () {
	int cnt = 0;
	while (cnt <= 5) {
		PL_GoStop ();
		delay (500);
		cnt++;
		Move_Gotime (150, 170);
		//delay (500);
	}
	PL_GoLineTime (270);
	//Move_Stop ();
	//delay (500);
	PL_CrossRoad (1);

	cnt = 0;
	while (cnt <= 3) {
		PL_GoStop ();
		delay (500);
		cnt++;
		Move_Gotime (150, 170);
		//delay (500);
	}
	PL_GoLineTime (270);
	Move_Stop ();
	//delay (500);
	PL_CrossRoad (2);

	Move_Gotime (SPEED,1000);
	Move_Stop ();

	return 1;
	//PL_CrossRoad (1);
	
}
int CollectGoods () {

}