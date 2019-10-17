#pragma once
void Debugger_Init();

//向调试器发送变量监视
//name : 变量名
//value: 变量值
void Debugger_SetWatch(String name, long value);

void Debugger_SetWatch(String name, String value);

//管理读数据
void Debugger_DebugManagement();