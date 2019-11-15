#pragma once
#include "IncludeList.h"
#include "Pretest.h"
/*
int ExploreMaze (int opt) {
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
	PL_CrossRoad (opt);

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
	Move_GotimeWithoutStop(150, 1300);
	//delay (500);


	return 1;
	//PL_CrossRoad (1);

}*/
//15/25 15/22
/*
int GetBall()
{
	int cnt = 0;
	while (cnt<2)
	{
		if (Huidu_IsLine(1) || Huidu_IsLine(2) ||Huidu_IsLine(4)|| Huidu_IsLine(5)||Huidu_IsLine(3))Debugger_SetWatch("line","true"), delay(200),cnt++;

			PL_GoBlind(1);


	}
	while (!Manager_Time_TakeTime(123, 600))
		Move_GoSpeed(150,160);
	//¹°
	//Move_GotimeWithoutStop()
	Move_Stop();
	delay(1000);
	//while(!Manager_Time_TakeTime(123,300)) Move_GoSpeed(-250, -240);
	while (!Manager_Time_TakeTime(123, 800)) Move_GoSpeed(-250, -247);
	while (!Manager_Time_TakeTime(123, 800)) Move_GoSpeed(-250, -250);
	//Move_GotimeWithoutStop(-200, 2000);
	Move_Stop();

}*/
/*void GetBall2()
{
	int cnt = 0;
	while (true)
	{
		if (Huidu_IsLine(1) || Huidu_IsLine(2) || Huidu_IsLine(4) || Huidu_IsLine(5) || Huidu_IsLine(3)) { delay(200); break; }

			PL_GoBlind(1);


	}
	while (!Manager_Time_TakeTime(123, 1000))

		PL_GoBlind(1);
	while (!Manager_Time_TakeTime(123, 700))
		Move_GoSpeed(150, 160);

	//¹°
	//Move_GotimeWithoutStop()
	Move_Stop();
	delay(1000);
	//while (!Manager_Time_TakeTime(123, 300)) Move_GoSpeed(-250, -240);
	//while (!Manager_Time_TakeTime(123, 100)) Move_GoSpeed(-240, -250);

	while (!Manager_Time_TakeTime(123, 800)) Move_GoSpeed(-250, -247);
	while (!Manager_Time_TakeTime(123, 800)) Move_GoSpeed(-250, -250);

	Move_Stop();

}
*/
bool GetballBackReadytoTurnLeft() {
	const int standard_x = 6, standard_y = 210;
	const int eps_x = 5, eps_y = 2;
	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.Y - standard_y) < eps_y) {
		return 1;
	}
	return 0;
}
bool GetballBackReadyforAvoidEntrance() {
	const int standard_x = 149, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;

}
bool GetballBackReadytoGoLeft() {
	const int standard_x = 249, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}

bool GetballBackReadytoGobackBlind() {
	const int standard_x = 218, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());

	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}


bool GetballBackReadytoGobackBlind11() {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());
	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}
bool GetballReturnHome() {
	const int standard_x = 10, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord());
	if (abs(Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}


void GetballBackTurnLeft() {
	if (!Manager_Time_TakeTime(17, 200)) {
		Move_GoSpeed(150, 150);
	}
	Move_Stop();
	Motor_GoSpeed(-225, -80);
	delay(1400);
	Move_Stop();
}

void GetballBack(void) {
	/*	if (!Manager_Time_TakeTime (40, 200)) {
			PL_GoBackBlind ();
		}
		while (!MicroMove_IsPushed (2)) {
			Motor_GoSpeed (150, -150);
		}
		Move_Stop ();*/
	while (!GetballBackReadytoTurnLeft()) {
		PL_GoBackBlind(3);
	}
	//Move_Stop ();
	GetballBackTurnLeft();
	while (!GetballBackReadyforAvoidEntrance()) {
		PL_GoBackBlind(4);
	}
	//	Move_Stop ();
	while (!GetballBackReadytoGobackBlind11()) {
		//185
		Move_GoSpeed(-150, -160);
	}
	while (!GetballBackReadytoGobackBlind()) {
		PL_GoBackBlind(4);
	}
	while (!GetballBackReadytoGoLeft()) {
		Move_GoSpeed(-150, -150);
	}
	while (!GetballReturnHome()) {
		PL_GoBlind(1);
	}
	Move_Stop();
	return;
}
