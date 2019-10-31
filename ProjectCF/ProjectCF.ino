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


	Motor_Init();
 	Huidu_Init();
	Debugger_Init();
	Serial.begin(9600);
	Distance_Init();
	Arm_Init();
	Zigbee_Init();
	//Serial1.begin(115200);
	
}
void loop()
{
	while (true)
	{
		Motor_GoSpeed(150, 150);
		Debugger_DebugManagement();

		if (Zigbee_MessageRecord())
		{
			Debugger_SetWatch("Time", Game.Time);
			Debugger_SetWatch("State", Game.GameState);
			//Debugger_SetWatch("", Game.);
			//Debugger_SetWatch("", Game.Time);

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

