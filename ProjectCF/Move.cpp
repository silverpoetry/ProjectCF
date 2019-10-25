#include "IncludeList.h"
#include "Move.h"
#include <math.h>

long long Move_LastCnt1;

long long Move_LastCnt2;
double Motor_Rate = 1;
void Move_Refresh()
{
	Move_LastCnt1 = Motor_M1Cnt;
	Move_LastCnt2 = Motor_M2Cnt;
}
void Move_GoSpeed(int speed1, int speed2)
{
	Motor_GoSpeed(speed1, speed2);
	//Motor_Rate = double(speed1) / double(speed2);
}

void Move_KeepRate()
{
		int step1 = Motor_M1Cnt - Move_LastCnt1;
		int step2 = Motor_M2Cnt - Move_LastCnt2;

		double KP = 1;
		int err = (step2 - step1)  ;




		//if (Manager_Time_TakeTime (3, 100))
		//{
		//Debugger_SetWatch ("A", step1);
		sh (\n ActualSpeed1 is), pu (step1);
		sh (\n ActualSpeed2 is), pu (step2);
		sh (\n Err is), pu (err);
		sh (\n M1Speed is), pu (Motor_M1Speed);
		sh (\n M2Speed is), pu (Motor_M2Speed);

			Debugger_SetWatch ("ActualSpeed1", step1);
			Debugger_SetWatch ("ActualSpeed2", step2);
		//	lastcnt11 = Motor_M1Cnt;
		//	lastcnt12 = Motor_M2Cnt;
			Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
			Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));

			//Motor_GoSpeed (140, Motor_M2Speed + 1);


			//Motor_GoSpeed (250, Motor_M2Speed - int(KP*err));
		//Motor_GoSpeed (min(255,max(Motor_M1Speed + int(KP * err),0)), 120);
		//sh (\n err is ); pu (err);

		/*if (step1 > step2*Motor_Rate)
			Motor_GoSpeed(Motor_M1Speed-1, Motor_M2Speed);
		else if (step1 < step2*Motor_Rate)
			Motor_GoSpeed(Motor_M1Speed+1, Motor_M2Speed);*/
	
}