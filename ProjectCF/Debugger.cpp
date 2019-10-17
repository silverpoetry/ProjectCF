#include "IncludeList.h"
#include "Debugger.h"

void Debugger_SetWatch(String name, long  value)
{
	Serial1.print("SetWatch("+name+",");
	Serial1.print(value);
	Serial1.print(")\n");
	
}
void Debugger_SetWatch(String name, String value)
{
	Serial1.print("SetWatch(" + name + ","+value+")\n");
	
}
void Debugger_DebugManagement()
{
	if (Serial1.available() > 0)
	{
		//Serial1.println(Serial1.readStringUntil('\n'));
		String s1, s2, s3;
		s1 = Serial1.readStringUntil('(');
		s2 = Serial1.readStringUntil(',');
		s3 = Serial1.readStringUntil(')');
		//s1 s2 s3 分别为指令名 参数1 参数2 类似于 MyFunc(pm1,pm2)
		Serial1.readStringUntil('\n');
	/*	Debugger_SetWatch("s1", s1);
		Debugger_SetWatch("s2", s2);
		Debugger_SetWatch("s3", s3);*/
		if (s1 == "fuck")Debugger_SetWatch("fuck", s2+" fucks "+s3);
	}
}
