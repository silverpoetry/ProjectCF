#include "Patrol_Line.h"
#include <math.h>

#define SEP_EPS 100
#define MID_LINE 860

int sensor_a_value, sensor_b_value;
double PID_SumError = 0;
double PID_LastError = 0;
double PID_LastTime = 0;
int PL_LastPosition = 0;
//黑小白大
//right: mid:765 black:670 gray:880
//left: ...............665 .....960
/*
middle-range: 914/886 ~ 872/794 900/860 886/887
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


	if (Huidu_IsLine (sensor_a) && Huidu_IsLine (sensor_b)) {
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
int PL_GoStop () {
	int state = PL_PIDCorrection (1);
	if (state == 4) {
		Move_Stop ();
		return 1;
	}
	return 0;
}
int PID_Output (double newError, int& deltaerr)
{
	double deltatime = (micros () - PID_LastTime) / 100000;

	PID_SumError += newError * deltatime;
	double deltaError = (newError - PID_LastError) / deltatime;
	Debugger_SetWatch ("dt", deltaError);

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
	PID_SumError = 0;
	PID_LastError = 0;
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
		int cnt = 0;
		while (1) {
			delay (500);
			if (PL_Position (2, 3, 1, 4) == 1) {
				Move_Stop ();
				delay (1000);
				Move_RotateLeft ();//这一步复位
				return 1;
			}

			cnt++;
			if (cnt > 100) {
				break;
			}
		}
	}
	return 0;
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
		if (position_state == 1)
			PID_SumClear ();
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
		/*if (PID_SumError > 0) {
			PL_LastPosition = 2;
		}
		else if (PID_SumError < 0) {
			PL_LastPosition = 3;
		}*/
		int s;
		int output = PID_Output (Err, s);
		Motor_GoSpeed (SPEED + output, SPEED - output);
		//delay (20);
		if (Manager_Time_TakeTime (5, 100)) {
			Debugger_SetWatch ("Error", Err);
			Debugger_SetWatch ("derr", s);
			Debugger_SetWatch ("Output", output);
			Debugger_SetWatch ("M1Speed1", (Motor_M1Speed));
			Debugger_SetWatch ("M2Speed2", (Motor_M2Speed));
		}

	}

}
//return 0;
//}
int PL_GoStop () {
	PID_Refresh ();
	while (1)
	{
		if (PL_Position (2, 3, 1, 4) == 4) {
			Move_Stop (); break;
		}
		else {
			if (Manager_Time_TakeTime (20, 20)) {
				//PID_KP = 0.2, PID_KI = 0.1, PID_KD = 0.3;
				PL_PIDCorrection (1);
			}
		}
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
*/
void PL_goline (int basic1, int basic2)
{
	if (Huidu_IsLine (1) && Huidu_IsLine (2))Motor_GoSpeed (basic1, basic2);

	if (Huidu_IsLine (1))Motor_GoSpeed (basic1, basic2 * 1.2);
	if (Huidu_IsLine (2))Motor_GoSpeed (basic1 * 1.4, basic2);
	if (Huidu_IsLine (3))Motor_GoSpeed (-100, -100), delay (50), Motor_GoSpeed (0, 0), delay (2000);


}