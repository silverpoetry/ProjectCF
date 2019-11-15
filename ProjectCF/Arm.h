#pragma once


#include <Arduino.h>
#include <Servo.h>


const int Arm_Pins[] = { 4,5,2,46 };


void Arm_Init();

void Arm_Reset(int opt);

void Arm_Go(int n, int angel);
void Arm_Go(int n, int angel, int deltime);
void Arm_PickBall();
void Arm_DropBall ();
