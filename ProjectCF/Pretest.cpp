#pragma once
#include "IncludeList.h"

int ExploreMaze () {
	int cnt = 0;
	while (cnt < 5) {
		PL_GoStop ();
		//delay (200);
		cnt++;
		Move_Gotime (150, 170);
		//delay (500);
	}
	PL_GoLineTime (270);
	//Move_Stop ();
	//delay (500);
	PL_CrossRoad (1);

	cnt = 0;
	while (cnt < 3) {
		PL_GoStop ();
		//delay (200);
		//cnt++;
		Move_Gotime (150, 170);
		cnt++;
		//delay (500);
	}
	PL_GoLineTime (270);
	Move_Stop ();
	//delay (500);
	PL_CrossRoad (2);

	PL_GoStop ();
	//delay (200);
	Move_Gotime (150, 170);


	Move_Gotime (SPEED,1500);
	Move_Stop ();

	return 1;
	//PL_CrossRoad (1);
	
}

int GetBall()
{
	int cnt = 0;
	while (cnt<2)
	{
		if (Huidu_IsLine(1) || Huidu_IsLine(2) || Huidu_IsLine(5)||Huidu_IsLine(3))Move_Stop(), delay(3000),cnt++;
		if (Manager_Time_TakeTime(123, 20))
		{
			PL_GoBlind();
		}

	}
	while (!Manager_Time_TakeTime(123, 100))
		PL_GoBlind();

	Motor_SetSpeed(-200, -200);
	delay(2000);
	Move_Stop();
	
}
int CollectGoods () {

}