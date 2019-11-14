#include "Patrol_Line.h"
#include <math.h>
#define PL_NormalSpeed 120

void PL_CrossRoad (int opt) {

	if (opt == 1) {
		Move_RotateLeft ();
		delay (300);
		while (1) {
			//delay (500);
			if (Huidu_IsLine (2)) {
				Move_Stop ();
				return;
			}

		}
	}
	else if (opt == 5) {
		Move_RotateRight ();
		delay (300);
		while (1) {
			//delay (500);
			if (Huidu_IsLine (5)) {
				Move_Stop ();
				return;
			}

		}
	}
	return;
}
#define SPEED2 150
void PL_PIDCorrection (int opt)
{
	bool is0 = Huidu_IsLine (1), is6 = Huidu_IsLine (6), is1 = Huidu_IsLine (2), is2 = Huidu_IsLine (3), is3 = Huidu_IsLine (4), is4 = Huidu_IsLine (5);
	if (opt == 1) {
		if (is2 && is3) {
			Motor_GoSpeed (SPEED, SPEED2); return;
		}

		if (is2)Motor_GoSpeed (SPEED * 0.93, SPEED2 * 1.07);
		if (is3)Motor_GoSpeed (SPEED * 1.07, SPEED2 * 0.93);
		if (is4)Motor_GoSpeed (SPEED * 1.3, SPEED2 * 0.7);
		if (is1)Motor_GoSpeed (SPEED * 0.7, SPEED2 * 1.3);
		if (is0)Motor_GoSpeed (SPEED * 1.4, SPEED2 * 0.6);

		if (is6)Motor_GoSpeed (SPEED * 0.6, SPEED2 * 1.4);
	}
#define SPEEDx 70
	else if (opt == 2) {
		if (is2 && is3) {
			Motor_GoSpeed (-SPEEDx, -SPEEDx); return;
		}

		if (is2)Motor_GoSpeed (-SPEEDx * 1.07, -SPEEDx * 0.93);
		if (is3)Motor_GoSpeed (-SPEEDx * 0.93, -SPEEDx * 1.07);
		if (is4)Motor_GoSpeed (-SPEEDx * 0.7, -SPEEDx * 1.3);
		if (is1)Motor_GoSpeed (-SPEEDx * 1.3, -SPEEDx * 0.7);
		if (is0)Motor_GoSpeed (-SPEEDx * 0.6, -SPEEDx * 1.4);

		if (is6)Motor_GoSpeed (-SPEEDx * 1.4, -SPEEDx * 0.6);
	}
}

void PL_GoLineTime (int time)
{
	while (!Manager_Time_TakeTime (31, time))
	{

		if (Manager_Time_TakeTime (21, 10))PL_PIDCorrection (1);
	}
}
void PL_GoCrossTurnLeft ()
{

	PL_GoWithoutStop ();
	//Move_GotimeWithoutStop(150, 100);
	PL_GoLineTime (110);
	Move_Stop ();
	PL_CrossRoad (1);


}
void PL_GoCrossTurnRight ()
{

	PL_GoWithoutStop ();
	//Move_GotimeWithoutStop(150, 200);
	PL_GoLineTime(110);
	Move_Stop ();
	PL_CrossRoad (5);


}
void PL_GoWithoutStop ()
{
	Motor_GoSpeed (SPEED, SPEED);
	while (1)
	{
		//if (Huidu_IsLine(1)) {  return; }
		if (Huidu_IsCrossRoad ()) { return; }
		if (Manager_Time_TakeTime (21, 10))PL_PIDCorrection (1);
	}
}

int PL_GoStop () {
	//PID_Refresh ();
	Motor_GoSpeed (SPEED, SPEED);
	//delay (2);
	while (1)
	{
		//if (Huidu_IsLine(1) )
		if (Huidu_IsCrossRoad ()) { Move_Stop (); return; }
		if (Manager_Time_TakeTime (21, 10))PL_PIDCorrection (1);

	}
}

void PL_GoBackStop () {
/*	Motor_GoSpeed (-SPEED+50, -SPEED+50);
	while (1) {
		//	if (Huidu_IsCrossRoad ()) cnt++;
		if (Huidu_IsCrossRoad ()) { Move_Stop (); break; }
		if (Manager_Time_TakeTime (21, 10))PL_PIDCorrection (2);
	}
	Move_Gotime (-SPEED+50, -SPEED+50, 300);
//	delay()
//	int cnt = 0;
	Motor_GoSpeed (-SPEED + 50, -SPEED + 50);
	while (1) {
	//	if (Huidu_IsCrossRoad ()) cnt++;
		if (Huidu_IsCrossRoad()) { Move_Stop (); break; }
		if (Manager_Time_TakeTime (21, 10))PL_PIDCorrection (2);
	}
	PL_GoLineTime (160);*/
	Move_GoSpeed (-150, -150);
	while (!Manager_Time_TakeTime(18,3000))
	{
		if (Manager_Time_TakeTime(19,20))
		{
			Move_KeepRate ();
		}
	}
	Move_Stop ();
}

void PL_GoBlind (int opt)
{

	if (opt == 1) {
		if (MicroMove_IsPushed (1))Motor_GoSpeed (155, 140);
		else Motor_GoSpeed (150, 155);
	}
	else if (opt == 2) {
		if (MicroMove_IsPushed (2))Motor_GoSpeed (140, 160);
		else Motor_GoSpeed (140, 155);
	}
}
void PL_GoBackBlind (int opt) {
	if (opt == 3) {
		if (MicroMove_IsPushed (3)) {
			Motor_GoSpeed (-150, -140);
			//Debugger_SetWatch ("m3", 1);
		}
		else {
			Motor_GoSpeed (-150, -175);
			//	Debugger_SetWatch ("m3", 0);
		}
	}
	else if (opt == 4) {
		if (MicroMove_IsPushed (4)) {
			Motor_GoSpeed (-140, -150);
		//	Debugger_SetWatch ("m3", 1);
		}
		else { 
			Motor_GoSpeed (-165, -150); //Debugger_SetWatch ("m3", 0); 
		}
	}
}
/*
void PL_goline (int basic1, int basic2)
{
	if (Huidu_IsLine (1) && Huidu_IsLine (2))Motor_GoSpeed (basic1, basic2);

	if (Huidu_IsLine (1))Motor_GoSpeed (basic1, basic2 * 1.2);
	if (Huidu_IsLine (2))Motor_GoSpeed (basic1 * 1.4, basic2);
	if (Huidu_IsLine (3))Motor_GoSpeed (-100, -100), delay (50), Motor_GoSpeed (0, 0), delay (2000);


}*/