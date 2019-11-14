#include "IncludeList.h"
#include "Debugger.h"
#include "Arduino.h"
#define serialPort Serial3
void Action();
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
int Debug_lspeed=150, Debug_rspeed=150;
void Debugger_DebugManagement()
{
	if (serialPort.available() > 0)
	{
		//serialPort.println(serialPort.readStringUntil('\n'));
		String s1, s2, s3;
		s1 = serialPort.readStringUntil('(');
		s2 = serialPort.readStringUntil(',');
		s3 = serialPort.readStringUntil(')');
		//s1 s2 s3 分别为指令名 参数1 参s数2 类似于 MyFunc(pm1,pm2)
		serialPort.readStringUntil('\n');
		/*	Debugger_SetWatch("s1", s1);
			Debugger_SetWatch("s2", s2);
			Debugger_SetWatch("s3", s3);*/
		if (s1 == "fuck")Debugger_SetWatch ("fuck", s2 + " fucks " + s3);
		else if (s1 == "fwd")Move_Refresh (), Motor_GoSpeed (atoi (s2.c_str ()), atoi (s3.c_str ()));
		else if (s1 == "amg1")Arm_Go (1, atoi (s2.c_str ()));
		else if (s1 == "amg2")Arm_Go (2, atoi (s2.c_str ()));
		else if (s1 == "glfwd")PL_GoStop ();
		else if (s1 == "sspeed")Debug_lspeed = atoi (s2.c_str ()), Debug_rspeed = atoi (s3.c_str ());
		else if (s1 == "gtm")Move_Gotime (Debug_lspeed, Debug_rspeed, atoi (s3.c_str ()));
		else if (s1 == "gllft")PL_GoCrossTurnLeft ();
		else if (s1 == "glrt")PL_GoBackBlind (4);
		else if (s1 == "bmpspeed")Move_GoSpeed (atoi (s2.c_str ()), atoi (s3.c_str ()));
		else if (s1 == "getball")PL_GoBlind (1);
		else if (s1 == "getball2")PL_GoBlind (2);
		else if (s1 == "exmaze")PL_GoBackBlind (3);
		else if (s1 == "getball2")PL_GoBlind (2);
		//else if (s1 == "exmaze")MT_Main();
		//else if (s1 == "getball2")GetBall2();

	}
	
}
