#include "IncludeList.h"
#include "Debugger.h"
#include "Arduino.h"
#define serial Serial3
void Debugger_Init()
{
	serial.begin(9600);
}

void Debugger_SetWatch(String name, long  value)
{
	
	serial.print("SetWatch("+name+",");
	serial.print(value);
	serial.print(")\n");
	
}
void Debugger_SetWatch(String name, String value)
{
	serial.print("SetWatch(" + name + ","+value+")\n");
	
}
void Debugger_DebugManagement()
{
	if (serial.available() > 0)
	{
		//serial.println(serial.readStringUntil('\n'));
		String s1, s2, s3;
		s1 = serial.readStringUntil('(');
		s2 = serial.readStringUntil(',');
		s3 = serial.readStringUntil(')');
		//s1 s2 s3 分别为指令名 参数1 参数2 类似于 MyFunc(pm1,pm2)
		serial.readStringUntil('\n');
		/*	Debugger_SetWatch("s1", s1);
			Debugger_SetWatch("s2", s2);
			Debugger_SetWatch("s3", s3);*/
		if (s1 == "fuck")Debugger_SetWatch("fuck", s2 + " fucks " + s3);
	}
	
}
