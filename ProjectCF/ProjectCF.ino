/*
 Name:		ProjectCF.ino
 Created:	2019/9/22 21:26:00
 Author:	The CFer
*/



#include <Servo.h>
#include <Esplora.h>
#include "IncludeList.h"
#include <Wire.h>
#include <Arduino.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/io.h>

void gopointY(int x)
{
	Outer_GoPointByY(x, 1);
}

void setup()
{


	
	Serial.begin(9600);
	Serial.println("123");
	Manager_Hardware_Init();
	Debugger_Init();
	Serial.println("1243");
	
	//Debugger_SetWatch("123", 123);
	GridHelper_Init();

	Serial.println("124343");
	

	//Serial1.begin(115200);

}


void loop()
{
	
	/*while (true)
	{
		Mpu_GoRelativeAngle(-68);
		delay(500);
	}*/
	
	Serial.print("2323");

	long long lastcnt11 = Motor_M1Cnt;
	long long lastcnt12 = Motor_M2Cnt;
	while (1)
	{
		//PL_GoBlind(2);
		
		
		
		
	//	delay(3000);
		//GridHelper_Go({ 2,1 }, { 7,5 });
		
		Debugger_DebugManagement();
		Debugger_SetWatch("aaa", "saa");
		Zigbee_MessageRecord();
		Debugger_ShowZigbee();
		Debugger_ShowMpu();
		Debugger_ShowDistance();
		Debugger_ShowMicroMove();
	/*	Serial.print("2323");
		Huidu_ShowValues();*/
		Huidu_ShowValues();
		Debugger_ShowDistance();
		//Debugger_SetWatch("12312", 123123);
		//Serial.println("123");
		//zigbee_show();

		if (Manager_Time_TakeTime(6, 100))
		{
			Debugger_SetWatch("ActualSpeed1", Motor_M1Cnt - lastcnt11);
			Debugger_SetWatch("ActualSpeed2", Motor_M2Cnt - lastcnt12);
			lastcnt11 = Motor_M1Cnt;
			lastcnt12 = Motor_M2Cnt;
		}
	}

	//	Move_GoSpeed (100, 100);
	//	Move_Refresh ();
	//	Motor_GoSpeed (180, 180);
	//	Move_Refresh ();
	//	Debugger_Init
	while (true)
	{
		//	PL_GoBackBlind ();
			//Arm_PickBall();
			//delay(3000);
		//	Motor_GoSpeed (150, 255);
		//	Serial.println ("123");
		Debugger_DebugManagement();
		//Huidu_ShowValues();
		//Zigbee_MessageRecord();
		Debugger_SetWatch("BallX", Game.BallPos.X);
		Debugger_SetWatch("BallY", Game.BallPos.Y);
		Debugger_SetWatch("Car1X", Car[0].pos.X);
		Debugger_SetWatch("car1Y", Car[0].pos.Y);
		Debugger_SetWatch("Car2X", Car[1].pos.X);
		Debugger_SetWatch("CAR2Y", Car[1].pos.Y);
		//Debugger_SetWatch("dis1", Distance_Get(1));
		//Debugger_SetWatch("dis2", Distance_Get(2));
		//Debugger_SetWatch("dis3", Distance_Get(3));
		////PL_GoBlind ();
	//	Move_KeepRate ();
		/*if (MicroMove_IsPushed (1)) {
			Serial.println (1);
		}

		if (MicroMove_IsPushed (2)) {
			Serial.println (2);

		}

		if (MicroMove_IsPushed (3)) {
			Serial.println (3);

		}

		if (MicroMove_IsPushed (4)) {
			Serial.println (4);

		}
		if (Manager_Time_TakeTime (14, 50)) {
			Move_KeepRate ();
		}*/
		//Debugger_SetWatch ("asd", "as");
		if (Manager_Time_TakeTime(23, 10))
		{
			//	if()
				/*
			//	Move_KeepRate ();
				Debugger_SetWatch ("h1", Huidu_Read (1));
				Debugger_SetWatch ("h2", Huidu_Read (2));
				Debugger_SetWatch ("h3", Huidu_Read (3));
				Debugger_SetWatch ("h4", Huidu_Read (4));
				Debugger_SetWatch ("h5", Huidu_Read (5));
				Debugger_SetWatch ("h6", Huidu_Read (6));

				Debugger_SetWatch ("us1", Distance_Get (1));
				Debugger_SetWatch ("us2", Distance_Get (2));
	*/

		}
		//MT_Main ();
		//ExploreMaze ();
	//	long long i = 0;
	//	Mpu_ShowValueInTestMode ();
	//	Debugger_SetWatch
	//	delay (1000);


	/*	if (Manager_Time_TakeTime (5, 100)) {
			Move_KeepRate ();
		}*/
		
		
	}


	//Motor_GoSpeed(120, 120);	//Move_GoSpeed (SPEED, SPEED);
	while (1) {
		Debugger_DebugManagement();
		//PL_GoStop ();
		//PL_GoStop
	}


}

