#include "IncludeList.h"
#include "Move.h"
#include <math.h>

long long Move_LastCnt1;

long long Move_LastCnt2;
double Motor_Rate=1;
void Move_Refresh()
{
	Move_LastCnt1 = Motor_M1Cnt;
	Move_LastCnt2 = Motor_M2Cnt;
}
void Move_GoSpeed(int speed1, int speed2)
{
	Motor_GoSpeed(speed1, speed2);
	Motor_Rate = double(speed1) / double(speed2);
}

void Move_KeepRate()
{
		int step1 = Motor_M1Cnt - Move_LastCnt1;
		if (Motor_M1Speed < 0)step1 *= -1;
		
		int step2 = Motor_M2Cnt - Move_LastCnt2;
		if (Motor_M2Speed < 0)step2 *= -1;
		double KP = 1.5;
		int err = (step2*Motor_Rate - step1)  ;

		//if (Manager_Time_TakeTime (3, 300))
		//{

			Debugger_SetWatch ("ActualSpeed1", step1);
			Debugger_SetWatch ("ActualSpeed2", step2);
		//	lastcnt11 = Motor_M1Cnt;
		//	lastcnt12 = Motor_M2Cnt;
			Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
			Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));
			//Debugger_SetWatch ("err", (err));

		//}
		Motor_GoSpeed (60, min (255, max (Motor_M2Speed - int (KP * err), 0)));
		//Motor_GoSpeed (min(255,max(Motor_M1Speed + int(KP * err),0)), 120);

		sh (\n err is ); pu (err);
/*
		if (step1 > step2*Motor_Rate)
			Motor_GoSpeed(Motor_M1Speed-1, Motor_M2Speed);
		else if (step1 < step2*Motor_Rate)
			Motor_GoSpeed(Motor_M1Speed+1, Motor_M2Speed);*/
	
}