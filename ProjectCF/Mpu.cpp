/*
This code is used for connecting arduino to serial mpu6050 module, and test in arduino uno R3 board.
connect map:
arduino   mpu6050 module
VCC    5v/3.3v
TX     RX<-0
TX     TX->1
GND    GND
note:
because arduino download and mpu6050 are using the same serial port, you need to un-connect 6050 module when you want to download program to arduino.
 Created 14 Nov 2013
 by Zhaowen

 serial mpu6050 module can be found in the link below:
 http://item.taobao.com/item.htm?id=19785706431
 */
#include "IncludeList.h"
#include "CFSPI.h"
#define SerialPort Serial1

float  Mpu_Angles[3];
void Mpu_Init() {
	// initialize serial:
	//SerialPort.begin(115200);
	SPI_Init(MASTER);
}





void Mpu_ReadData()
{
	//for (int i = 0; i < 3; i++)
	//{
	//	Mpu_ReadData2();
	//	//values[i] = Mpu_Angles[2];
	//}
	Mpu_Angles[2] = SPI_ReadAngle();
	delay(4);
	//Mpu_Angles[2] *= -1;
	/*qsort(values, 5, sizeof(float), cmpfunc);
	
	Mpu_Angles[2]= values[2];*/
}
float getdis(float angle)
{
	float ang = abs(angle - Mpu_Angles[2]);
	return min(ang, 360.0 - ang);
}

//angel:目标角度
//dir:方向
void Mpu_GoAngle(float angle,Mpu_dir dir)
{
	//左边是正
	if (dir== Right)
	{
		Mpu_ReadData();
		while (getdis(angle) > 5)
		{
			int dis = abs(getdis(angle));
			float rate = min(dis / 40, 1);
			Move_GoSpeed(dir * 50 * rate + 50, -dir * 50 * rate - 50);
			Mpu_ReadData();
		}
		Move_Stop();


	}
	else
	{
		Mpu_ReadData();
		while (getdis(angle) > 5)
		{
			int dis = abs(getdis(angle));
			float rate = min(dis / 40, 1);
			Move_GoSpeed(-dir * 50 * rate - 50, dir * 50 * rate + 50);
			Mpu_ReadData();
		}
		Move_Stop();
	}
		
}
int os(float speed)
{
	int abssp = abs(speed);
	int sig = Manager_Signal(speed);
	return sig * max(abssp, 50);
}
void Mpu_GoRelativeAngle(int angel)
{
	Mpu_ReadData();
	float nowangle = Mpu_Angles[2];
	Debugger_SetWatch("ang", Mpu_Angles[2]);
	while (getdis(nowangle) < abs(angel))
	{
		int dis = abs(angel) - getdis(nowangle);
		float rate = min(dis / 40, 1);
		Debugger_SetWatch("err", getdis(nowangle));
		Move_GoSpeed(os(Manager_Signal(angel) * 100*rate),os( -Manager_Signal(angel) * 100*rate));
		Mpu_ReadData();
	}
	
	Move_Stop();

}

void Mpu_GoRelativeAngleAAA (int angel)
{
	Mpu_ReadData ();
	Debugger_SetWatch("ang", Mpu_Angles[2]);
	float nowangle = Mpu_Angles[2];
	while (getdis (nowangle) < abs (angel))
	{

		int dis = abs(angel) - getdis(nowangle);
		float rate = min(dis / 40, 1);
		Debugger_SetWatch("err", getdis(nowangle));
		if (Manager_Signal (angel)>0)
		{
			Move_GoSpeed (os(120*rate), 0);
		}
		else
		{
			Move_GoSpeed (0, os(120*rate));
		}


	
		Mpu_ReadData ();
	}
	//Debugger_SetWatch ("err", getdis (nowangle));
	Move_Stop ();
//	Debugger_SetWatch ("ang", Mpu_Angles[2]);
}
void Mpu_GoRelativeAngleSetSpeed (int angel,int speed1 ,int speed2)
{
	Mpu_ReadData ();
	float nowangle = Mpu_Angles[2];
	while (getdis (nowangle) < abs (angel))
	{
	

		Move_GoSpeed (speed1,speed2 );
		Mpu_ReadData ();
	}
	Debugger_SetWatch ("err", getdis (nowangle));
	Move_Stop ();
	Debugger_SetWatch ("ang", Mpu_Angles[2]);
}


void Mpu_ResetZ()
{
	SerialPort.print(0xFF);
	SerialPort.print(0xAA);
	SerialPort.print(0x52);
}
float _tmpangle=0;
void Mpu_RecordAngle()
{
	Mpu_ReadData();
	 _tmpangle = Mpu_Angles[2];
}
float getreladis(float ang1, float ang2)
{
	if (ang1 < 0)ang1 += 360;
	if (ang2 < 0)ang2 += 360;
	float v = ang2 - ang1;
	float v2 = 360.0 - abs(v);
	v2 *= (-1 * Manager_Signal(v));
	return abs(v)<abs(v2) ? v : v2;
}

void Mpu_AdjustStraight(int speed)
{
	Mpu_ReadData();
	float angle = Mpu_Angles[2];
	
	int level =Manager_Signal(getreladis(angle, _tmpangle))*(abs( getreladis(angle , _tmpangle))+5) / 5;
	level *= Manager_Signal (speed);
	Debugger_SetWatch("level", level);
	if (level == 0)Move_GoSpeed(speed, speed);
	else if (level == -1)Move_GoSpeed(speed*1.1, speed*0.9);
	else if (level == 1)Move_GoSpeed(speed*0.9, speed*1.1);
	else if (level == -2)Move_GoSpeed(speed*1.2, speed*0.8);
	else if (level == 2)Move_GoSpeed(speed*0.8, speed*1.2);
	else if (level == -3)Move_GoSpeed(speed*1.3, speed*0.7);
	else if (level == 3)Move_GoSpeed(speed*0.7, speed*1.3);
	else if (level > 0)Move_GoSpeed(speed*0.6, speed*1.4);
	else Move_GoSpeed(speed*1.4, speed*0.6);
	

}