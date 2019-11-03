#include "Patrol_Line.h"
#include <math.h>


void PL_CrossRoad (int opt) {
	
	if (opt == 1) {
		Move_RotateLeft ();
		delay(400);
		while (1) {
			//delay (500);
			if (Huidu_IsLine(2)) {
				Move_Stop ();
				return;
			}
			
		}
	}
	else if (opt == 2) {
		Move_RotateRight ();
		delay (400);
		while (1) {
			//delay (500);
			if (Huidu_IsLine (6)) {
				Move_Stop ();
				return;
			}

		}
	}
	return ;
}
#define SPEED2 150
void PL_PIDCorrection()
{
	bool is1 = Huidu_IsLine(2), is2 = Huidu_IsLine(3), is3 = Huidu_IsLine(4), is4 = Huidu_IsLine(5);
	if (is2 && is3) {
		Motor_GoSpeed(SPEED, SPEED2); return;
	}

	if (is2)Motor_GoSpeed(SPEED*0.9, SPEED2*1.1);
	if (is3)Motor_GoSpeed(SPEED*1.1, SPEED2*0.9);
	if(is4)Motor_GoSpeed(SPEED*1.3, SPEED2*0.7);
	if (is1)Motor_GoSpeed(SPEED*0.7, SPEED2*1.3);
	
}

void PL_GoLineTime(int time)
{
	while (!Manager_Time_TakeTime(31,time))
	{
		
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
	}
}
void PL_GoCrossTurnLeft()
{
	
		PL_GoWithoutStop();
		Move_GotimeWithoutStop(150, 200);
		PL_GoLineTime(280);
		PL_CrossRoad(1);
	
	
}
void PL_GoCrossTurnRight ()
{
	
		PL_GoWithoutStop ();
		Move_GotimeWithoutStop(150, 200);
		PL_GoLineTime (230);
		PL_CrossRoad (2);
	

}
void PL_GoWithoutStop()
{
	Motor_GoSpeed(SPEED, SPEED);
	while (1)
	{
		//if (Huidu_IsLine(1)) {  return; }
		if (Huidu_IsCrossRoad ()) { return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
	}
}
int PL_GoStop () {
	//PID_Refresh ();
	Motor_GoSpeed(SPEED, SPEED);
	//delay (2);
	while (1)
	{
		//if (Huidu_IsLine(1) )
		if(Huidu_IsCrossRoad()){ Move_Stop(); return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();

	}
}
void PL_GoBlind ()
{
	
		if (MicroMove_IsPushed ())Motor_GoSpeed (155, 140);
		else Motor_GoSpeed (140, 155);

	
}/*
void PL_goline (int basic1, int basic2)
{
	if (Huidu_IsLine (1) && Huidu_IsLine (2))Motor_GoSpeed (basic1, basic2);

	if (Huidu_IsLine (1))Motor_GoSpeed (basic1, basic2 * 1.2);
	if (Huidu_IsLine (2))Motor_GoSpeed (basic1 * 1.4, basic2);
	if (Huidu_IsLine (3))Motor_GoSpeed (-100, -100), delay (50), Motor_GoSpeed (0, 0), delay (2000);


}*/