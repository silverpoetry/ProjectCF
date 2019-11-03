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
		long long i = 0;
		if (Zigbee_MessageRecord ()) {
			Debugger_SetWatch ("arrive", ++i);
		}

		if (Manager_Time_TakeTime(1,100))
		{
			Debugger_SetWatch ("switch", MicroMove_IsPushed ());

			/*Rep(i, 1, 6)
			{
				String s = "huidu";
				Debugger_SetWatch(s + i, Huidu_Read(i));
			}*/
			Debugger_SetWatch ("X1", Car[0].pos.X);
			Debugger_SetWatch ("Y1", Car[0].pos.Y);
			Debugger_SetWatch ("X2", Car[1].pos.X);
			Debugger_SetWatch ("Y2", Car[1].pos.Y);
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

