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




void setup ()
{
	
	
	
	Serial.begin (9600);
	Serial.println ("123");
	Manager_Hardware_Init ();
	Debugger_Init ();
	Serial.println ("1243");


	//Serial1.begin(115200);

}
void loop ()
{
//	Move_GoSpeed (100, 100);
	Move_Refresh ();
	long long lastcnt11 = Motor_M1Cnt;
	long long lastcnt12 = Motor_M2Cnt;
	while (true)
	{
	//	Serial.println ("123");
		Debugger_DebugManagement ();
		Debugger_SetWatch ("asd", "as");
		if (Manager_Time_TakeTime(23,20))
		{
			Move_KeepRate ();
		}
		//MT_Main ();
		//ExploreMaze ();
	//	long long i = 0;
	//	Mpu_ShowValueInTestMode ();
	//	Debugger_SetWatch
	//	delay (1000);
		

	/*	if (Manager_Time_TakeTime (5, 100)) {
			Move_KeepRate ();
		}
		if (Manager_Time_TakeTime(6,1000))
		{
			Debugger_SetWatch ("ActualSpeed1", Motor_M1Cnt - lastcnt11);
			Debugger_SetWatch ("ActualSpeed2", Motor_M2Cnt - lastcnt12);
			 lastcnt11 = Motor_M1Cnt;
			 lastcnt12 = Motor_M2Cnt;
		}
		*/
	}


	//Motor_GoSpeed(120, 120);	//Move_GoSpeed (SPEED, SPEED);
	while (1) {
		Debugger_DebugManagement ();
		//PL_GoStop ();
		//PL_GoStop
	}


}

