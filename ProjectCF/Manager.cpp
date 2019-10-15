#include "IncludeList.h"
void Manager_Hardware_Init()
{
	Distance_Init();
	Mpu_Init();
	Arm_Init();
	Huidu_Init();
	Motor_Init();

}
long long StartTime[200] ;
bool isstarted[200] ;

bool Manager_Time_TakeTime(long index,long num)
{
	if (!isstarted[index])
	{
		isstarted[index] = true;
		StartTime[index] = millis();
		return false;
	}
	else if (millis() - StartTime[index] >= num)
	{
		isstarted[index] = false;
		return  true;
	}

	return false;

}


