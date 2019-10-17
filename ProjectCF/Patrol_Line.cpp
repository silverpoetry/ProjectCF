#include "Patrol_Line.h"
#include <math.h>

#define SEP_EPS 10

//判断在车与线的相对位置
int Patrol_Line_Position (int sensor_a, int sensor_b)
{
	if (abs(Huidu_Read(sensor_a) - Huidu_Read(sensor_b) < SEP_EPS)) {
		return 1; 
	}
	return 0;
}

int Patrol_Line_PIDCorrection (void)
{
	return 0;
}

void Patrol (void)
{
	Huidu_Init ();
}
