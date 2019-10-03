#include <Arduino.h>
#include "Console.h"
#define inputPin  4 // 定义超声波信号接收接口
#define outputPin  5// 定义超声波信号发出接口
void Distance_Init();
long Distance_Get();
