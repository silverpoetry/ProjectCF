#include "Patrol_Line.h"
#include <math.h>








void PL_CrossRoad (int opt) {
	
	if (opt == CrossRoad_Left) {
		Move_RotateLeft ();
		delay(400);
		int cnt = 0;
		while (1) {
			//delay (500);
			if (Huidu_IsLine(3)) {
				Move_Stop ();
				delay (1000);
				//Move_RotateLeft ();//这一步复位
			\
			}
			
		}
	}
	return ;
}
#define SPEED2 170
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
		if (Huidu_IsLine(1)) { return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
	}
}
void PL_GoCrossTurnLeft()
{
	while (true)
	{
		PL_GoWithoutStop();
		Move_Gotime(150, 170);
		PL_GoLineTime(280);
		PL_CrossRoad(1);
	}
	
}
void PL_GoWithoutStop()
{
	Motor_GoSpeed(SPEED, SPEED);
	while (1)
	{
		if (Huidu_IsLine(1)) {  return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
	}
}
int PL_GoStop () {
	//PID_Refresh ();
	Motor_GoSpeed(SPEED, SPEED);
	//delay (2);
	while (1)
	{
		if (Huidu_IsLine(1) ) { Move_Stop(); return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
		

	}
}

void PL_goline (int basic1, int basic2)
{
	if (Huidu_IsLine (1) && Huidu_IsLine (2))Motor_GoSpeed (basic1, basic2);

	if (Huidu_IsLine (1))Motor_GoSpeed (basic1, basic2 * 1.2);
	if (Huidu_IsLine (2))Motor_GoSpeed (basic1 * 1.4, basic2);
	if (Huidu_IsLine (3))Motor_GoSpeed (-100, -100), delay (50), Motor_GoSpeed (0, 0), delay (2000);


}