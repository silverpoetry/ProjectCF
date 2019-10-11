#include "IncludeList.h"
void Manager_Hardware_Init()
{
	Distance_Init();
	Mpu_Init();
	Arm_Init();
	Huidu_Init();
	Motor_Init();

}
long long StartTime= 0 ;
bool isstarted = false;
bool Manager_Time_TakeTime(int num)
{
	if (!isstarted)
	{
		isstarted = true;
		StartTime = micros();
		return false;
	}
	else if (micros() - StartTime >= num)
	{
		isstarted = false;
		return  true;
	}

	return false;

}


