#pragma once

#include "IncludeList.h"


void Go_Straight (int speed, int time);
void Go_Straight (int speed);//time = infinite

void Go_Back (int speed, int time);

void Turn_Right (int time);
void Turn_Left (int time);

void Rotate_Right (int time, int angle);
void Rotate_Left (int time, int angle);