#include "Outer.h"
#include "IncludeList.h"
void Outer_GoPointByX(int finalposition,int switchid)
{
	//从当前位置贴墙走点，以X为判别标准
	
	
	//获取当前位置
	while (!Zigbee_MessageRecord());
	int sig = Manager_Signal(OurCar.pos.X - finalposition);
	while (1)
	{


	//每隔30ms读取一次Zigbee信息
	
	Zigbee_MessageRecord();
	PL_GoBlind(switchid);
	if ((sig*(OurCar.pos.X - finalposition) < (Outer_eps ))&& sig*(OurCar.pos.X - finalposition) > (-30))break;
	
		
	
	}
}

void Outer_GoPintByY(int finalposition, int switchid)
{
	//从当前位置贴墙走点，以Y为判别标准
	//从当前位置贴墙走点，以X为判别标准


	while (!Zigbee_MessageRecord());
	int sig = Manager_Signal(OurCar.pos.Y - finalposition);
	while (1)
	{




		Zigbee_MessageRecord();
		PL_GoBlind(switchid);
		if ((sig*(OurCar.pos.Y - finalposition) < (Outer_eps)) && sig*(OurCar.pos.Y - finalposition) > (-30))break;



	}
}
