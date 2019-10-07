#pragma once

//hjjhj

#include <Arduino.h>
#include <Servo.h>
//htchtfhtfh
//ÄãºÃ

const int Arm_Pins[] = { 44,3,2,46 };


void Arm_Init();

void Arm_Reset();

void Arm_Go(int n, int angel);
void Arm_Go(int n, int angel, int deltime);