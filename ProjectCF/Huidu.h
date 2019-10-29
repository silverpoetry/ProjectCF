#pragma once

#include <Arduino.h>

const int Huidu_Pins[] = {A1,A6,A5,A8};

extern int Huidu_LineValues[] ;

void Huidu_Init();
int Huidu_Read(int index);
boolean Huidu_IsLine(int index);

void Huidu_ShowValue();