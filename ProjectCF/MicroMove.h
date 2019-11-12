#pragma once
#define MicroMove_Pin A12 //left_front
#define MicroMove_Pin2 48 //right_front
#define MicroMove_Pin3 45 //left_back
#define MicroMove_Pin4 49 //right_back

void MicroMove_Init ();
bool MicroMove_IsPushed (int opt);
