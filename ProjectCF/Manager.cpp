#include "IncludeList.h"
#include "Manager.h"
#include "MainTask.h"
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
long long StartTime[100] ;
bool isstarted[100] ;

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

int Manager_Signal(long x)
{
	return x / abs(x);
}

