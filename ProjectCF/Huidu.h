#pragma once

#include <Arduino.h>

const int Huidu_Pins[] = {A10,A8,A11,A9,A5};

extern int Huidu_LineValues[] ;

void Huidu_Init();
int Huidu_Read(int index);
boolean Huidu_IsLine(int index);

void Huidu_ShowValue();