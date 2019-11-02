#include "Patrol_Line.h"
#include <math.h>








void PL_CrossRoad (int opt) {
	
	if (opt == 1) {
		Move_RotateLeft ();
		delay(400);
		int cnt = 0;
		while (1) {
			//delay (500);
			if (Huidu_IsLine(2)) {
				Move_Stop ();
				return;

				
			
			}
			
		}
	}
	return ;
}

#define PL_Speed2 150
#define PL_Speed1 150
void PL_GolineCorrect()
{
	
	
	bool is1 = Huidu_IsLine(2), is2 = Huidu_IsLine(3), is3 = Huidu_IsLine(4), is4 = Huidu_IsLine(5);
	if (is2 && is3) {
		Motor_GoSpeed(PL_Speed1, PL_Speed2); return;
	}

	if (is2)Motor_GoSpeed(PL_Speed1*0.9, PL_Speed2*1.1);
	if (is3)Motor_GoSpeed(PL_Speed1*1.1, PL_Speed2*0.9);
	if(is4)Motor_GoSpeed(PL_Speed1*1.3, PL_Speed2*0.7);
	if (is1)Motor_GoSpeed(PL_Speed1*0.7, PL_Speed2*1.3);
	

}

void PL_GoLineTime(int time)
{
	while (!Manager_Time_TakeTime(31,time))
	{
		if (Huidu_IsLine(1)) { return; }
		if (Manager_Time_TakeTime(21, 20))PL_GolineCorrect();
	}
}
void PL_GoCrossTurnLeft()
{
		PL_GoWithoutStop();
		Move_Gotime(150, 150);
		PL_GoLineTime(280);
		PL_CrossRoad(1);
	
}
void PL_GoWithoutStop()
{
	Motor_GoSpeed(PL_Speed1, PL_Speed2);
	while (1)
	{
		if (Huidu_IsLine(1)) {  return; }
		if (Manager_Time_TakeTime(21, 20))PL_GolineCorrect();
	}
}
int PL_GoStop () {
	//PID_Refresh ();
	Motor_GoSpeed(PL_Speed1, PL_Speed2);
	//delay (2);
	while (1)
	{
		if (Huidu_IsLine(1) ) { Move_Stop(); return; }
		if (Manager_Time_TakeTime(21, 20))PL_GolineCorrect();
		

	}
}


