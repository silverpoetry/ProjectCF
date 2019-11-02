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



void setup()
{
	Manager_Hardware_Init();
	Debugger_Init();
	Serial.begin(9600);
	
	
	//Serial1.begin(115200);
	
}
void loop()
{
	while (true)
	{
		
		Debugger_DebugManagement();
		//ExploreMaze ();

		if (Manager_Time_TakeTime(1,100))
		{
			Debugger_SetWatch ("switch", MicroMove_IsPushed ());
			for (int  i = 1; i < 7; i++)
			{
				String s = "huidu";

				Debugger_SetWatch(s + i, Huidu_Read(i));
			}
		}
	}

	
		//Motor_GoSpeed(120, 120);
	long long lastcnt11 = Motor_M1Cnt;
	long long lastcnt12 = Motor_M2Cnt;
	long long lastcnt21 = Motor_M1Cnt;
	long long lastcnt22 = Motor_M2Cnt;
	
	//Move_GoSpeed (SPEED, SPEED);
	while (1) {
		Debugger_DebugManagement ();
		//PL_GoStop ();
		//PL_GoStop
	}
	

}

