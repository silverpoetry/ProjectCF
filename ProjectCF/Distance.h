#include <Arduino.h>

#define Distance_InputPin  A14 // 定义超声波信号接收接口
#define Distance_OutPutPin  A15// 定义超声波信号发出接口
#define Distance_InputPin2  47 // 定义超声波信号接收接口
#define Distance_OutPutPin2  46// 定义超声波信号发出接口
void Distance_Init();
long Distance_Get(int opt);
//2, 3, 1 for left, right, front