#pragma once

#include <Arduino.h>

const int Huidu_Pins[] = {A12,A11,A10,A9,A8,A3};

extern int Huidu_LineValues[] ;

void Huidu_Init();
int Huidu_Read(int index);
bool Huidu_IsLine(int index, int value);
bool Huidu_IsLine(int index);

void Huidu_ShowValue();
bool Huidu_IsCrossRoad (void);