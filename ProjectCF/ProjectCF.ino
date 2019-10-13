/*
 Name:		ProjectCF.ino
 Created:	2019/9/22 21:26:00
 Author:	The CFer
*/

#define pu(a) Serial.print((a))
#define sh(a) Serial.print(#a)
#include <Wire.h>
#include <Arduino.h>
#include <stdlib.h>
#include "IncludeList.h"

void setup ()
{
	Motor_Init ();
	Huidu_Init ();
	Serial.begin (9600);


}
void loop ()
{
	/*if (Manager_Time_TakeTime(1000))
	{
		sh(The Motor 1 goes),pu((unsigned long)Motor_M1Cnt), sh(steps\n);
		sh(The Motor 2 goes), pu((unsigned long)Motor_M2Cnt), sh(steps\n);
	}*/
	/*if (Serial.available() > 0)
	{
		String s ;
		s =Serial.readString();
		sh(Motor),pu(s),sh(-   listening\n);

		if (atoi(s.c_str()) == 1)
		{
			while (Serial.available() == 0);
			s = Serial.readString();
			Serial.println(atoi(s.c_str()));
			sh(Motor1  go as), pu(atoi(s.c_str())), sh(- speed\n);
			Motor_SetSpeed(1, atoi(s.c_str()));
		}
		else if (atoi(s.c_str()) == 2)
		{
			while (Serial.available() == 0);
			s = Serial.readString();
			sh(Motor2  go as),pu(atoi(s.c_str())),sh(- speed\n);
			Motor_SetSpeed(2, atoi(s.c_str()));
		}
		else if (atoi(s.c_str()) == 3)
		{
			int a, b;
			while (Serial.available() == 0);
			s = Serial.readString();
			a = atoi(s.c_str());
			while (Serial.available() == 0);
			s = Serial.readString();
			b = atoi(s.c_str());
			sh(Motor1  go as), pu(a), sh(- speed\n);
			sh(Motor2  go as), pu(b), sh(- speed\n);
			Motor_GoSpeed(a, b);
		}
	}
	*/
	long long ind = 0;
	while (1)
	{
		Rep (i, 1, 4)
		{
			sh (HUIDU), pu (i), sh(" "), pu (Huidu_Read (i)), sh (\n);
		}
		delay (500);
	}
}
