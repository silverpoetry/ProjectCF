#include "Outer.h"
#include "IncludeList.h"
void Outer_GoPointByX(int finalposition,int switchid)
{
	//�ӵ�ǰλ����ǽ�ߵ㣬��XΪ�б��׼
	
	
	//��ȡ��ǰλ��
	while (!Zigbee_MessageRecord());
	int sig = Manager_Signal(OurCar.pos.X - finalposition);
	while (1)
	{


	//ÿ��30ms��ȡһ��Zigbee��Ϣ
	
	Zigbee_MessageRecord();
	PL_GoBlind(switchid);
	if ((sig*(OurCar.pos.X - finalposition) < (Outer_eps ))&& sig*(OurCar.pos.X - finalposition) > (-30))break;
	
		
	
	}
}

void Outer_GoPintByY(int finalposition, int switchid)
{
	//�ӵ�ǰλ����ǽ�ߵ㣬��YΪ�б��׼
	//�ӵ�ǰλ����ǽ�ߵ㣬��XΪ�б��׼


	while (!Zigbee_MessageRecord());
	int sig = Manager_Signal(OurCar.pos.Y - finalposition);
	while (1)
	{




		Zigbee_MessageRecord();
		PL_GoBlind(switchid);
		if ((sig*(OurCar.pos.Y - finalposition) < (Outer_eps)) && sig*(OurCar.pos.Y - finalposition) > (-30))break;



	}
}
