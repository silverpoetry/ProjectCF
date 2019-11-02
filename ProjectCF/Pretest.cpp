#pragma once
#include "IncludeList.h"
#include "Pretest.h"
int ExploreMaze () {
	int cnt = 0;
	while (cnt < 5) {
		PL_GoWithoutStop ();
		//delay (200);
		cnt++;
		Move_GotimeWithoutStop (150, 170);
		//delay (500);
	}
	PL_GoLineTime (270);
	//Move_Stop ();
	//delay (500);
	PL_CrossRoad (1);

	cnt = 0;
	while (cnt < 4) {
		PL_GoWithoutStop ();
		//delay (200);
		//cnt++;
		Move_GotimeWithoutStop (150, 170);
		cnt++;
		//delay (500);
	}
	//PL_GoLineTime (270);
	Move_GotimeWithoutStop(150, 1000);
	//delay (500);
	

	return 1;
	//PL_CrossRoad (1);
	
}

int GetBall()
{
	int cnt = 0;
	while (cnt<2)
	{
		if (Huidu_IsLine(1) || Huidu_IsLine(2) ||Huidu_IsLine(4)|| Huidu_IsLine(5)||Huidu_IsLine(3))Debugger_SetWatch("line","true"), delay(200),cnt++;
		
			PL_GoBlind();
	

	}
	while (!Manager_Time_TakeTime(123, 450))
		Move_GoSpeed(150,160);
	//¹°
	//Move_GotimeWithoutStop()
	Move_Stop();
	delay(1000);
	//while(!Manager_Time_TakeTime(123,300)) Move_GoSpeed(-250, -240);
	while (!Manager_Time_TakeTime(123, 1000)) Move_GoSpeed(-250, -245);
	while (!Manager_Time_TakeTime(123, 1000)) Move_GoSpeed(-250, -250);
	//Move_GotimeWithoutStop(-200, 2000);
	Move_Stop();
	
}
void GetBall2()
{
	int cnt = 0;
	while (true)
	{
		if (Huidu_IsLine(1) || Huidu_IsLine(2) || Huidu_IsLine(4) || Huidu_IsLine(5) || Huidu_IsLine(3)) { delay(200); break; }
		
			PL_GoBlind();
		

	}
	while (!Manager_Time_TakeTime(123, 1000))

		PL_GoBlind();
	while (!Manager_Time_TakeTime(123, 450))
		Move_GoSpeed(150, 160);
	
	//¹°
	//Move_GotimeWithoutStop()
	Move_Stop();
	delay(1000);
	//while (!Manager_Time_TakeTime(123, 300)) Move_GoSpeed(-250, -240);
	//while (!Manager_Time_TakeTime(123, 100)) Move_GoSpeed(-240, -250);

	while (!Manager_Time_TakeTime(123, 1000)) Move_GoSpeed(-250, -245);
	while (!Manager_Time_TakeTime(123, 1000)) Move_GoSpeed(-250, -250);

	Move_Stop();

}

int CollectGoods () {

}