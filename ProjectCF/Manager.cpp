#include "IncludeList.h"
void Manager_Hardware_Init()
{
	Motor_Init ();
	Huidu_Init ();
	Distance_Init ();
	//Arm_Init ();
	Zigbee_Init (); 
	MicroMove_Init ();
	Mpu_Init ();

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


