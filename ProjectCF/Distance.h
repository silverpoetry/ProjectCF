#include <Arduino.h>

#define Distance_InputPin  A14 // ���峬�����źŽ��սӿ�
#define Distance_OutPutPin  A15// ���峬�����źŷ����ӿ�
#define Distance_InputPin2  47 // ���峬�����źŽ��սӿ�
#define Distance_OutPutPin2  46// ���峬�����źŷ����ӿ�
void Distance_Init();
long Distance_Get(int opt);
//2, 3, 1 for left, right, front