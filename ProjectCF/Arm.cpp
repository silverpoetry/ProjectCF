#include "Arm.h"
#include "IncludeList.h"
Servo servos[4];
int angels[4] = {0,55,100};

//��ʼ����е�۵Ķ��������λ����ʼ�Ƕ�
void Arm_Init()
{	
	servos[0].attach(Arm_Pins[0],500,2500);
	servos[1].attach(Arm_Pins[1], 500, 2500);
	
	
	Arm_Reset(1);
	Arm_Reset (2);
	delay(500);
}
//��λ��е�۵�Ĭ��λ��
void Arm_Reset(int opt)
{
	Arm_Go(opt, angels[opt]);
	delay(300);
	//Arm_Go(2, angels[2]);
}

//����ָ�������ת��ָ���Ƕ�
//n:�����ţ�1-4��
//angel����ת���ĽǶ�
void Arm_Go(int n, int angel)
{
	Debugger_SetWatch("asd", "Fuck3");
	int delaytime = 13;
	Debugger_SetWatch("asd", "Fuck2");
	switch (n)
	{
	case 1:
		
		delaytime = 8;
		break;
	case 2:
		delaytime = 14;
		
		break;
	
	}
	
	if (angel >= angels[n-1])
		for (int i = angels[n - 1]; i <= angel; i++)
		{
			/*if (n == 4 && abs(i - angel) >= 10 && abs(i - angel) <=20)delaytime =20+( 20-abs(i - angel))*2;
			servos[n - 1].write(i); delay(delaytime);
			if (n == 4 && abs(i - angel) <= 10)delaytime = 40;*/
				servos[n - 1].write(i); delay(delaytime);
		}
	
	if (angel <  angels[n - 1])
		for (int i = angels[n - 1]; i >= angel; i--)
		{
			/*if (n == 4 && abs(i - angel) >= 10 && abs(i - angel) <= 20)delaytime = 20 + (20 - abs(i - angel)) * 2;
			servos[n - 1].write(i); delay(delaytime);
			if (n == 4 && abs(i - angel) <= 10)delaytime = 40;*/
			servos[n - 1].write(i); delay(delaytime);
		}
	
	angels[n - 1] = angel;

}

void Arm_Go(int n, int angel, int deltime)
{
	int delaytime = deltime;
	

	if (angel >= angels[n - 1])
		for (int i = angels[n - 1]; i <= angel; i++)
		{
			/*if (n == 4 && abs(i - angel) >= 10 && abs(i - angel) <=20)delaytime =20+( 20-abs(i - angel))*2;
			servos[n - 1].write(i); delay(delaytime);
			if (n == 4 && abs(i - angel) <= 10)delaytime = 40;*/
			servos[n - 1].write(i); delay(delaytime);
		}

	if (angel <  angels[n - 1])
		for (int i = angels[n - 1]; i >= angel; i--)
		{
			/*if (n == 4 && abs(i - angel) >= 10 && abs(i - angel) <= 20)delaytime = 20 + (20 - abs(i - angel)) * 2;
			servos[n - 1].write(i); delay(delaytime);
			if (n == 4 && abs(i - angel) <= 10)delaytime = 40;*/
			servos[n - 1].write(i); delay(delaytime);
		}

	angels[n - 1] = angel;

}