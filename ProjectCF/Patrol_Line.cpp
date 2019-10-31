#include "Patrol_Line.h"
#include <math.h>
#ifndef Xiancchang
#define SEP_EPS 100
#define MID_LINE 650
#else
#define SEP_EPS 100
#define MID_LINE 640
#endif // !Xiancchang


double PID_KP = 0.2, PID_KI = 0.1, PID_KD = 0.3;
int sensor_a_value, sensor_b_value;
double PID_SumError = 0;
double PID_LastError = 0;
double PID_LastTime = 0;
int PL_LastPosition = 0;
//黑小白大
//right: mid:765 black:670 gray:880
//left: ...............665 .....960
/*
middle-range: 551/477  
slightly_left: 958/716 951/702
........right: 788/849 790/849 783/856

largely_left:954/693 963/693 890/726
.......right:710/883 734/880 717/890 700/883

right: 724/878 686/884 692/889
left: 947/657 940/589

200

*/



//判断在车与线的相对位置
int PL_Position (int sensor_a, int sensor_b, int sensor_c, int sensor_d)
{
	sensor_a_value = Huidu_Read (sensor_a), sensor_b_value = Huidu_Read (sensor_b);

	Debugger_SetWatch ("A", sensor_a_value);
	Debugger_SetWatch ("B", sensor_b_value);

	//if()

	if (Huidu_IsLine (sensor_a, sensor_a_value) && Huidu_IsLine (sensor_b, sensor_b_value)) {
		return 4; //到路口了
	}

	//在线上
	if (abs (sensor_a_value - MID_LINE) < SEP_EPS / 2 && abs (sensor_b_value - MID_LINE) < SEP_EPS / 2) {
		PL_LastPosition = 0;
		return 1;
	}
	//完全偏离
	if (abs (sensor_a_value - sensor_b_value < SEP_EPS)) {

		//不在线上
		if (sensor_a_value < MID_LINE - SEP_EPS && sensor_b_value < MID_LINE - SEP_EPS) {
			return 0;
		}

	}
	/*
	//偏右
	else if (sensor_a_value > Huidu_LineValues[sensor_a] && sensor_b_value < Huidu_LineValues[sensor_b]) {
		return 2;
	}

	//偏左
	else if (sensor_a_value < Huidu_LineValues[sensor_a] && sensor_b_value > Huidu_LineValues[sensor_b]) {
		return 3;
	}*/
	//}
}
int PID_Output (double newError, int& deltaerr)
{
	double deltatime = (micros () - PID_LastTime) / 100000;

	PID_SumError += newError * deltatime;
	double deltaError = (newError - PID_LastError) / deltatime;
	Debugger_SetWatch ("dt", deltatime);

	int output = PID_KP * newError + PID_KI * PID_SumError + PID_KD * deltaError;
	//Debugger_SetWatch ("Output", output);

	//Move_GoSpeed (Motor_M1Speed + output, Motor_M2Speed - output);

	PID_LastTime = micros ();
	//delay(10);
	PID_LastError = newError;
	deltaerr = deltaError;
	return output;
}
void PID_SumClear ()
{
	PID_SumError = 0;

}
void PID_Refresh ()
{
	PL_Position (2, 3, 1, 4);
	int Err = (sensor_a_value - sensor_b_value);
	if (abs (Err) < SEP_EPS) {
		Err = 0;
	}
	if (Err > 0) {
		//PL_LastPosition = 2;
		Err = max (Err - SEP_EPS, 0);
	}
	else if (Err < 0) {
		//	PL_LastPosition = 3;
		Err = min (Err + SEP_EPS, 0);
	}
	PID_SumError = 0;
	PID_LastError = Err;
	PID_LastTime = micros();

}

int PL_FindCenter (int time) {
	Move_GoSpeed (100, 100);
	delay (time);
	Move_Stop ();
	return 1;
}

int PL_CrossRoad (int opt) {
	if (opt == 1) {
		Move_RotateLeft ();
		delay(400);
		int cnt = 0;
		while (1) {
			//delay (500);
			if (Huidu_IsLine(3)) {
				Move_Stop ();
				delay (1000);
				//Move_RotateLeft ();//这一步复位
				return 1;
			}
			/*
			cnt++;
			if (cnt > 100) {
				break;
			}*/
		}
	}

	else if (opt == 2) {
		Move_RotateRight ();
		delay (400);
		int cnt = 0;
		while (1) {
			//delay (500);
			if (Huidu_IsLine (4)) {
				Move_Stop ();
				delay (1000);
				//Move_RotateLeft ();//这一步复位
				return 1;
			}
			/*
			cnt++;
			if (cnt > 100) {
				break;
			}*/
		}
	}
	return 0;
}
void PL_PIDCorrection()
{
	/*if (Huidu_IsLine(1)&&Huidu_IsLine(2)&&Huidu_IsLine(3)&&Huidu_IsLine(4）)
	{

	}*/
	
	bool is1 = Huidu_IsLine(2), is2 = Huidu_IsLine(3), is3 = Huidu_IsLine(4), is4 = Huidu_IsLine(5);
	if (is2 && is3) {
		Motor_GoSpeed(SPEED, SPEED); return;
	}
	 
	if (is2)Motor_GoSpeed(SPEED*0.9, SPEED*1.1);
	if (is3)Motor_GoSpeed(SPEED*1.1, SPEED*0.9);
	if(is4)Motor_GoSpeed(SPEED*1.3, SPEED*0.7);
	if (is1)Motor_GoSpeed(SPEED*0.7, SPEED*1.3);
	

}
int PL_PIDCorrection (int opt)
{
	int cnt = 0;
	int position_state = PL_Position (2, 3, 1, 4);
	//while (1) {
		//delay (100);
		//sensor_b_value = analogRead(A5);

//单光感-右2左3
	/*	if (opt == 2 || opt == 3) {
			//PL_Position (2, 3, 1, 4);
			int Err = (opt==2?sensor_b_value:sensor_a_value) - MID_LINE;
			if (abs (Err) < SEP_EPS) {
				PID_Refresh ();
				return 1;
			}

			//output = PID_KP * newError + PID_KI * PID_SumError + PID_KD * deltaError;
			int delerrrr;
			PID_KP = 0.2, PID_KI = 1e-7, PID_KD = 0.3;
			int output = PID_Output (Err,delerrrr);


			//Motor_GoSpeed(Motor_Spee)
			if (opt == 2) {
				Motor_GoSpeed (SPEED + output, SPEED - output);
			}
			else if (opt == 3) {
				Motor_GoSpeed (SPEED - output, SPEED + output);
			}
		//	delay (100);
			//Move_KeepRate ();
			//Move_Refresh ();

			if (Manager_Time_TakeTime (5, 100)) {
				Debugger_SetWatch ("Err", Err);
				Debugger_SetWatch ("Output", output);
				Debugger_SetWatch ("A", sensor_a_value);
				Debugger_SetWatch ("B", sensor_b_value);
				Debugger_SetWatch ("derr", delerrrr);
			}
			cnt++;
		}*/
	if (opt == 1) {
		//if (position_state == 1)
			//PID_SumClear ();
		//continue;
	//else if (position_state == 4) {
	//	Move_Stop ();
	//	return 4;
		//delay (1000);

	//}
	/*else if (position_state == 0) {
		if (PL_LastPosition == 2) {
			PL_PIDCorrection (1);
		}*/
		/*	else if (PL_LastPosition == 3) {
				PL_PIDCorrection (3);
			}
		}*/
		//Err为正，说明左地灰更白，车向左偏，应向右调，左轮加速，右轮减速
		//黑的值小
		int Err = (sensor_a_value - sensor_b_value);
		if (abs (Err) < SEP_EPS) {
			Err = 0;
		}
		if (Err > 0) {
			//PL_LastPosition = 2;
			Err = max (Err - SEP_EPS, 0);
		}
		else if (Err < 0) {
			//	PL_LastPosition = 3;
			Err = min (Err + SEP_EPS, 0);
		}

		if (Err * PID_LastError <= 0) {
			PID_SumClear ();
		}

		/*if (PID_SumError > 0) {
			PL_LastPosition = 2;
		}
		else if (PID_SumError < 0) {
			PL_LastPosition = 3;
		}*/
		int s;
		int output = PID_Output (Err, s);
		Debugger_SetWatch ("sumerr", PID_SumError);

		Motor_GoSpeed (SPEED + output, SPEED - output);
		//delay (20);
		//if (Manager_Time_TakeTime (5, 100)) {
			Debugger_SetWatch ("Error", Err);
			//Debugger_SetWatch ("derr", s);
			Debugger_SetWatch ("Output", output);
			////Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
			//Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));
		//}

	}

}
//return 0;
//}
void PL_GoLineTime(int time)
{
	while (!Manager_Time_TakeTime(31,time))
	{
		if (Huidu_IsLine(1)) { return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
	}
}
void PL_GoCrossTurnLeft()
{
	while (true)
	{
		PL_GoWithoutStop();
		Move_Gotime(150, 170);
		PL_GoLineTime(280);
		PL_CrossRoad(1);
	}
	
}
void PL_GoWithoutStop()
{
	Motor_GoSpeed(SPEED, SPEED);
	while (1)
	{
		if (Huidu_IsLine(1)) {  return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
	}
}
int PL_GoStop () {
	//PID_Refresh ();
	Motor_GoSpeed(SPEED, SPEED);
	//delay (2);
	while (1)
	{
		if (Huidu_IsLine(1) ) { Move_Stop(); return; }
		if (Manager_Time_TakeTime(21, 20))PL_PIDCorrection();
		

	//			  
	//	Debugger_SetWatch ("kp", 1000*PID_KP);
	//	Debugger_SetWatch ("ki", 1000*PID_KI);
	//	Debugger_SetWatch ("kd", 1000*PID_KD);
	//	int position_state = PL_Position (2, 3, 1, 4);
	//	if (position_state == 4) {

	//		Debugger_SetWatch ("state", "stop");
	//		Move_Stop (); break;
	//	}
	//	else {

	//		if (position_state == 1)
	//			PID_SumClear ();
	//		if (Manager_Time_TakeTime (20, 10)) {
	//			//Debugger_SetWatch ("state", "go");
	//			//PID_KP = 0.2, PID_KI = 0.1, PID_KD = 0.3;
	//			PL_PIDCorrection (1);
	//		}
	//	}
	}
}
/*
int Patrol (void)
{
	int state;
	while (1) {
		int position_state = PL_Position (2, 3, 1, 4);
		if (position_state == 4) {
			state = PL_PIDCorrection (1);
		}

		if (state == 4) {
			if (PL_FindCenter (500)) {
				if (PL_CrossRoad (1)) {
					return 1;
				}
				else {//转弯没有找到线
					Move_Stop ();
					return 0;
					//break;
				}
			}
		}
		else if(state == 1){
			return 1;
		}
	}
}
*//*
void PL_goline (int basic1, int basic2)
{
	if (Huidu_IsLine (1) && Huidu_IsLine (2))Motor_GoSpeed (basic1, basic2);

	if (Huidu_IsLine (1))Motor_GoSpeed (basic1, basic2 * 1.2);
	if (Huidu_IsLine (2))Motor_GoSpeed (basic1 * 1.4, basic2);
	if (Huidu_IsLine (3))Motor_GoSpeed (-100, -100), delay (50), Motor_GoSpeed (0, 0), delay (2000);


}*/