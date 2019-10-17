#include "IncludeList.h"
#include "Move.h"

long long Move_LastCnt1;

long long Move_LastCnt2;
double Motor_Rate;
void Move_Refresh()
{
	Move_LastCnt1 = Motor_M1Cnt;
	Move_LastCnt1 = Motor_M2Cnt;
}
void Move_GoSpeed(int speed1, int speed2)
{
	Motor_GoSpeed(speed1, speed2);
	Motor_Rate = speed1 / speed2;
}

void Move_KeepRate()
{
	
		int step1 = Motor_M1Cnt - Move_LastCnt1;
		int step2 = Motor_M2Cnt - Move_LastCnt2;
		if (step1 > step2*Motor_Rate)
			Motor_GoSpeed(Motor_M1Speed-1, Motor_M2Speed);
		else if (step1 < step2*Motor_Rate)
			Motor_GoSpeed(Motor_M1Speed+1, Motor_M2Speed);
		Move_LastCnt1 = Motor_M1Cnt;
		Move_LastCnt2 = Motor_M2Cnt;
	
}