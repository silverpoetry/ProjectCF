#include "IncludeList.h"
#include "Debugger.h"
#include "Arduino.h"
#define serialPort Serial3

void left()
{
	//Move_GotimeWithoutStop(150, 50);
	
	PL_GoLineTime(300);
	Move_Stop();
	PL_CrossRoad(5);
}
void rt()
{
	//Move_GotimeWithoutStop(150, 50);

	PL_GoLineTime(300);
	Move_Stop();
	PL_CrossRoad(1);
}
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
int Debug_lspeed = 150, Debug_rspeed = 150, Debug_ptx = 0, Debug_ptY = 0; int n = 0;
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
#pragma region 电机
		else if (s1 == "fwd")Motor_GoSpeed(atoi(s2.c_str()), atoi(s3.c_str()));
		else if (s1 == "sspeed")Debug_lspeed = atoi(s2.c_str()), Debug_rspeed = atoi(s3.c_str());
		else if (s1 == "gtm")Move_Gotime(Debug_lspeed, Debug_rspeed, atoi(s3.c_str()));
		
#pragma endregion
#pragma region MPU
		else if (s1 == "gstm")	Move_GoStraightTime(Debug_lspeed, atoi(s3.c_str()));
		else if (s1 == "relat")Mpu_GoRelativeAngle(atoi(s2.c_str()));
		else if (s1 == "relata")Mpu_GoRelativeAngleAAA(atoi(s2.c_str()));
		else if (s1 == "abt")Mpu_GoAngle(atoi(s2.c_str()), Mpu_dir::Left);
		else if (s1 == "setz")Mpu_ResetZ();
#pragma endregion

#pragma region 机械臂
		else if (s1 == "amg1")Arm_Go(1, atoi(s2.c_str()));
		else if (s1 == "amg2")Arm_Go(2, atoi(s2.c_str()));
#pragma endregion

#pragma region 寻线

		else if (s1 == "glfwd")PL_GoStop();
		else if (s1 == "gllft")PL_GoCrossTurnLeft();
		else if (s1 == "glrt")PL_GoCrossTurnRight();
#pragma endregion
#pragma region 走位
		else if (s1 == "zxx")Outer_GoPointByX(atoi(s2.c_str()), 1);
		else if (s1 == "yxx")Outer_GoPointByX(atoi(s2.c_str()), 2);
		else if (s1 == "zxy")Outer_GoPointByY(atoi(s2.c_str()), 1);
		else if (s1 == "yxy")Outer_GoPointByY(atoi(s2.c_str()), 2);
#pragma endregion

#pragma region 任务
		else if (s1 == "getball2")PL_GoBlind(1);
		else if (s1 == "exmaze")MainTask_CollectGoods();
		else if (s1 == "fuction0")PL_GoBlind(1);
		else if (s1 == "fuction1")PreContest_EasyMaze();
		else if (s1 == "fuction2")PL_GoBlind(2);
		else if (s1 == "fuction3")MainTask_CollectGoods();
		else if (s1 == "fuction4")Move_GoStraightTime(150, 3000);
		else if (s1 == "fuction5")PreContest_SavePeople();
#pragma endregion

#pragma region 地图
		else if (s1 == "setpoint")Debug_ptx = atoi(s2.c_str()), Debug_ptY = atoi(s3.c_str());
		else if (s1 == "setdir")Graph[Debug_ptx][Debug_ptY][atoi(s2.c_str())] = -1, Debugger_SetWatch("n", ++n);
		else if (s1 == "grinit")GridHelper_Init2(), Debugger_SetWatch("init2", "true");
		else if (s1 == "grclear")GridHelper_Init(), Debugger_SetWatch("init1", "true");
#pragma endregion



		
		
		
	
		
		
	
		
		
		
		
		//else if (s1 == "exmaze")MT_Main();
		//else if (s1 == "getball2")GetBall2();

	}
	
}

void Debugger_ShowMicroMove()
{
	Debugger_SetWatch("switch1", MicroMove_IsPushed(1));
	Debugger_SetWatch("switch2", MicroMove_IsPushed(2));
}
void Debugger_ShowDistance()
{
	Debugger_SetWatch("dis1", Distance_Get(1));
	Debugger_SetWatch("dis2", Distance_Get(2));
	Debugger_SetWatch("dis3", Distance_Get(3));
}


String makepoint(Pos p)
{
	String s = "";
	s = s + p.X;
	s = s + "|";
	s = s + p.Y;
	return s;
}
void Debugger_ShowMpu()
{

	Mpu_ReadData();
	Debugger_SetWatch("mpu", Mpu_Angles[2]);
}
void Debugger_ShowZigbee()

{
	Zigbee_MessageRecord();
	Debugger_SetWatch("car", makepoint(OurCar.pos));
	Debugger_SetWatch("psg1", makepoint(Passenger[0].pos));
	Debugger_SetWatch("psg2", makepoint(Passenger[1].pos));
	Debugger_SetWatch("psg1nd", makepoint(GridHelper_PositionConverter(Passenger[0].pos)));
	Debugger_SetWatch("psg2nd", makepoint(GridHelper_PositionConverter(Passenger[1].pos)));
	Debugger_SetWatch("GAME", Game.GameState);
	Debugger_SetWatch("BALL", makepoint(Game.BallPos));

}
