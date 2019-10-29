#pragma once
#define Rep(i,a,b) for(int i = a ;i<=b ;i++)
#define Dwn(i,a,b) for(int i = a ;i >=b ;i--)
#define pu(a) Serial.print((a))
#define sh(a) Serial.print(#a)
#include <Arduino.h>
#include "Mpu.h"
#include "Huidu.h"
#include "Distance.h"
#include "Motor.h"
#include "Arm.h"
#include "Manager.h"
#include "Debugger.h"
#include "Move.h"
#include "Zigbee.h"
#include "Patrol_Line.h"

#define SPEED 160