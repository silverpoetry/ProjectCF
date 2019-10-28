#include "Arm.h"

Servo servos[4];
int angels[4] = {0,180,170,108 };

//初始化机械臂的舵机，并归位到初始角度
void Arm_Init()
{	
	servos[0].attach(Arm_Pins[0],500,2500);
	servos[1].attach(Arm_Pins[1], 500, 2500);
	
	
	Arm_Reset();
	delay(500);
}
//复位机械臂到默认位置
void Arm_Reset()
{
	Arm_Go(1, angels[1]);
	delay(300);
	Arm_Go(2, angels[2]);
}

//控制指定舵机旋转到指定角度
//n:电机编号（1-4）
//angel：旋转到的角度
void Arm_Go(int n, int angel)
{
	int delaytime = 13;
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