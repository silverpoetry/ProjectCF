#include "Patrol_Line.h"
#include <math.h>
#define PL_NormalSpeed 120

void PL_CrossRoad (int opt) {

	if (opt == 1) {
		Move_RotateLeft ();
		delay (300);
		while (1) {
			//delay (500);
			if (Huidu_IsLine (3)) {
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
			if (Huidu_IsLine (4)) {
				Move_Stop ();
				return;
			}

		}
	}
	return;
}

void PL_PIDCorrection (int opt)
{
	bool isone = Huidu_IsLine (1), issix = Huidu_IsLine (6), istwo = Huidu_IsLine (2), isthree = Huidu_IsLine (3), isfour = Huidu_IsLine (4), isfive = Huidu_IsLine (5);
	if (opt == 1) {

		//if (issix)Motor_GoSpeed(SPEED * 1.3, SPEED2 * 0.7);
		//else  if (isone)Motor_GoSpeed(SPEED * 0.7, SPEED2 * 1.3);
		//else  if (istwo)Motor_GoSpeed(SPEED * 0.8, SPEED2 * 1.2);
		// else if (isfive)Motor_GoSpeed(SPEED * 1.2, SPEED2 * 0.8);
		//else if (isthree && isfour) {
		//	Motor_GoSpeed (SPEED, SPEED2); return;
		//}
		//else if (isthree)Motor_GoSpeed (SPEED * 0.9, SPEED2 * 1.1);
		//else if (isfour)Motor_GoSpeed(SPEED * 1.1, SPEED2 * 0.9);
		
	 if (isthree && isfour) {
		Motor_GoSpeed (SPEED, SPEED2); return;
	}
	 else	if (issix)Motor_GoSpeed (SPEED * 1.3, SPEED2 * 0.3);
		else  if (isone)Motor_GoSpeed (SPEED * 0.3, SPEED2 * 1.3);
		else  if (istwo)Motor_GoSpeed (SPEED * 0.5, SPEED2 * 1.2);
		else if (isfive)Motor_GoSpeed (SPEED * 1.2, SPEED2 * 0.5);
	
		else if (isthree)Motor_GoSpeed (SPEED * 0.92, SPEED2 * 1.05);
		else if (isfour)Motor_GoSpeed (SPEED * 1.05, SPEED2 * 0.92);
		

		
	}
#define SPEEDx 100
	else if (opt == 2) {
		if (isthree && isfour) {
			Motor_GoSpeed (-SPEEDx, -SPEEDx); return;
		}

		if (isfour)Motor_GoSpeed (-SPEEDx * 1.1, -SPEEDx * 0.9);
		if (isthree)Motor_GoSpeed (-SPEEDx * 0.9, -SPEEDx * 1.1);
		if (istwo)Motor_GoSpeed (-SPEEDx * 0.7, -SPEEDx * 1.3);
		if (isfive)Motor_GoSpeed (-SPEEDx * 1.3, -SPEEDx * 0.7);
		if (issix)Motor_GoSpeed (-SPEEDx * 0.6, -SPEEDx * 1.4);

		if (isone)Motor_GoSpeed (-SPEEDx * 1.4, -SPEEDx * 0.6);
	}
}

void PL_GoLineTime (int time)
{
	Move_GoSpeed(150, 150);
	while (!Manager_Time_TakeTime (31, time))
	{

		if (Manager_Time_TakeTime (21, 10))PL_PIDCorrection (1);
	}
}
void PL_GoCrossTurnLeft ()
{

	PL_GoWithoutStop ();
	//Move_GotimeWithoutStop(150, 100);
	PL_GoLineTime (100);
	Move_Stop ();
	PL_CrossRoad (1);


}
void PL_GoCrossTurnRight ()
{

	PL_GoWithoutStop ();
	//Move_GotimeWithoutStop(150, 200);
	PL_GoLineTime(100);
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
		if (true)PL_PIDCorrection (1);
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
		if (true)PL_PIDCorrection (1);

	}
}

void PL_GoBackStop () {
	Move_Stop();
	delay(200);
	Move_Gotime(-150,-150, 300);
	while (1) {
		//	if (Huidu_IsCrossRoad ()) cnt++;
		if (Huidu_IsCrossRoad()) { Move_Stop(); break; }
		if (Manager_Time_TakeTime(21, 10))PL_PIDCorrection(2);
	}
/*	Motor_GoSpeed (-SPEED+50, -SPEED+50);
	
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
	/*Move_GoSpeed (-150, -150);
	while (!Huidu_IsCrossRoad());*/
	/*while (!Manager_Time_TakeTime(18,3000))
	{
		if (Manager_Time_TakeTime(19,20))
		{
			Move_KeepRate ();
		}
	}*/
	Move_Stop ();
}

void PL_GoBlind (int opt)
{

	if (opt == 1) {
		if (MicroMove_IsPushed (1))Motor_GoSpeed (160, 140);
		else Motor_GoSpeed (150, 170);
	}
	else if (opt == 2) {
		if (MicroMove_IsPushed (2))Motor_GoSpeed (140, 160);
		else Motor_GoSpeed (180, 140);
	}
	else if (opt == 3) {
		if (MicroMove_IsPushed(3)) {
			Motor_GoSpeed(-150, -140);
			//Debugger_SetWatch ("m3", 1);
		}
		else {
			Motor_GoSpeed(-150, -175);
			//	Debugger_SetWatch ("m3", 0);
		}
	}
	else if (opt == 4) {
		if (MicroMove_IsPushed(4)) {
			Motor_GoSpeed(-140, -150);
			//	Debugger_SetWatch ("m3", 1);
		}
		else {
			Motor_GoSpeed(-165, -150); //Debugger_SetWatch ("m3", 0); 
		}
	}
}
void PL_GoBlind(int opt,int speed)
{

	if (opt == 1) {
		if (MicroMove_IsPushed(1))Motor_GoSpeed(speed*1.2, speed*0.8);
		else Motor_GoSpeed(speed*0.8, speed*1.2);
	}
	else if (opt == 2) {
		if (MicroMove_IsPushed(2)) Motor_GoSpeed(speed*0.8, speed*1.2);
		else Motor_GoSpeed(speed*1.2, speed*0.8);
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