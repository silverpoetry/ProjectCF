#include "IncludeList.h"
#include "Debugger.h"
#include "Arduino.h"
#define serialPort Serial3
void Debugger_Init()
{
	serialPort.begin(9600);
}

void Debugger_SetWatch(String name, long  value)
{
	
	serialPort.print("SetWatch("+name+",");
	serialPort.print(value);
	serialPort.print(")\n");
	
}
void Debugger_SetWatch(String name, String value)
{
	serialPort.print("SetWatch(" + name + ","+value+")\n");
	
}
void Debugger_DebugManagement()
{
	if (serialPort.available() > 0)
	{
		//serialPort.println(serialPort.readStringUntil('\n'));
		String s1, s2, s3;
		s1 = serialPort.readStringUntil('(');
		s2 = serialPort.readStringUntil(',');
		s3 = serialPort.readStringUntil(')');
		//s1 s2 s3 �ֱ�Ϊָ���� ����1 ����2 ������ MyFunc(pm1,pm2)
		serialPort.readStringUntil('\n');
		/*	Debugger_SetWatch("s1", s1);
			Debugger_SetWatch("s2", s2);
			Debugger_SetWatch("s3", s3);*/
		if (s1 == "fuck")Debugger_SetWatch("fuck", s2 + " fucks " + s3);
	}
	
}