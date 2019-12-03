#include "Outer.h"
#include "IncludeList.h"

void Outer_GoPointByX(int finalposition, int switchid)
{
	//�ӵ�ǰλ����ǽ�ߵ㣬��XΪ�б��׼	//��ȡ��ǰλ��
	while (!Zigbee_MessageRecord());
	bool flag = false;
	int distance = abs(OurCar.pos.X - finalposition);
	if (distance > 50)flag = true;
	int sig = Manager_Signal(OurCar.pos.X - finalposition);
	while (1)
	{		//ÿ��30ms��ȡһ��Zigbee��Ϣ

		Zigbee_MessageRecord();
		distance = abs(OurCar.pos.X - finalposition);
		if (flag&&distance<30)
		{
			PL_GoBlind(switchid,70);
		}
		else
		{
			PL_GoBlind(switchid);
		}
		
		Debugger_SetWatch("err", sig*(OurCar.pos.Y - finalposition));
		if ((sig*(OurCar.pos.X - finalposition) < (Outer_eps)) )break;
	}
	Move_Stop();
}

void Outer_GoPointByY(int finalposition, int switchid)
{
	//�ӵ�ǰλ����ǽ�ߵ㣬��YΪ�б��׼
	//�ӵ�ǰλ����ǽ�ߵ㣬��XΪ�б��׼	
	while (!Zigbee_MessageRecord());
	bool flag = false;
	int distance = abs(OurCar.pos.X - finalposition);
	if (distance > 50)flag = true;
	int sig = Manager_Signal(OurCar.pos.Y - finalposition);
	Debugger_SetWatch("sig", sig);
	while (1)
	{

		Zigbee_MessageRecord();
		distance = abs(OurCar.pos.X - finalposition);
		if (flag&&distance < 30)
		{
			PL_GoBlind(switchid, 70);
		}
		else
		{
			PL_GoBlind(switchid);
		}
		
		Debugger_SetWatch("err", sig*(OurCar.pos.Y - finalposition));
		if ((sig*(OurCar.pos.Y - finalposition) < (Outer_eps)) )break;
	}
	Move_Stop();
}

void Outer_GoStraightPointByY (int finalposition) {
	int sig = Manager_Signal (OurCar.pos.Y - finalposition);
	Mpu_RecordAngle();
	while (1)
	{
		Zigbee_MessageRecord ();
		
		Mpu_AdjustStraight(150);
		Debugger_SetWatch("err", sig*(OurCar.pos.Y - finalposition));
		if ((sig*(OurCar.pos.Y - finalposition) < (Outer_eps)))break;
	}
	Move_Stop();
}


void Outer_GoStraightPointByX (int finalposition) {
	int sig = Manager_Signal (OurCar.pos.Y - finalposition);
	Mpu_RecordAngle();
	while (1)
	{
		Zigbee_MessageRecord ();
		
		Mpu_AdjustStraight(150);
		Debugger_SetWatch("err", sig*(OurCar.pos.Y - finalposition));
		if ((sig*(OurCar.pos.X - finalposition) < (Outer_eps)))break;
	}
	Move_Stop();
}
