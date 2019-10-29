#include <Arduino.h>

#define Distance_InputPin  24 // 定义超声波信号接收接口
#define Distance_OutPutPin  22// 定义超声波信号发出接口
void Distance_Init();
long Distance_Get();