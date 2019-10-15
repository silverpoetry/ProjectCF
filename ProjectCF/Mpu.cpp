#include "Mpu.h"
#include "IncludeList.h"
#include <Kalman.h>
#include <Wire.h>
#include <Math.h>

float fRad2Deg = 57.295779513f; //将弧度转为角度的乘数
#define MPU_ADDR  0x68 //MPU-6050的I2C地址
const int Mpu_Valcnt = 7; //一次读取寄存器的数量

float Mpu_Roll = 0.0f; //上一次滤波得到的Roll角
float Mpu_Pitch = 0.0f; //上一次滤波得到的Pitch角
float Mpu_RollRate = 0.0f;
float Mpu_PitchRate = 0.0f;
float Mpu_Yaw = 0.0f;
float Mpu_YawRate = 0.0f;


const int nCalibTimes = 1000; //校准时读数的次数
int calibData[Mpu_Valcnt]; //校准数据




unsigned long Mpu_Lasttime = 0; //上一次读数的时间

Kalman kalmanRoll; //Roll角滤波器
Kalman kalmanPitch; //Pitch角滤波器
Kalman kalmanYaw;

//向MPU6050写入一个字节的数据
//指定寄存器地址与一个字节的值
void Mpu_WriteReg(int nReg, unsigned char nVal) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(nReg);
	Wire.write(nVal);
	Wire.endTransmission(true);
}

//从MPU6050读出一个字节的数据
//指定寄存器地址，返回读出的值
unsigned char Mpu_ReadReg(int nReg) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(nReg);
	Wire.requestFrom(MPU_ADDR, 1, true);
	Wire.endTransmission(true);
	return Wire.read();
}

//从MPU6050读出加速度计三个分量、温度和三个角速度计
//保存在指定的数组中
void ReadAccGyr(int* pVals) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(0x3B);
	Wire.requestFrom(MPU_ADDR, Mpu_Valcnt * 2, true);
	Wire.endTransmission(true);
	for (long i = 0; i < Mpu_Valcnt; ++i) {
		pVals[i] = Wire.read() << 8 | Wire.read();
	}
}


//对大量读数进行统计，校准平均偏移量
void Calibration()
{
	float valSums[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0 };
	//先求和
	for (int i = 0; i < nCalibTimes; ++i) {
		int mpuVals[Mpu_Valcnt];
		
		ReadAccGyr(mpuVals);
		for (int j = 0; j < Mpu_Valcnt; ++j) {
			valSums[j] += mpuVals[j];
		}
	}
	//再求平均
	for (int i = 0; i < Mpu_Valcnt; ++i) {
		calibData[i] = int(valSums[i] / nCalibTimes);
	}

	//calibData[2] += 16384; //设芯片Z轴竖直向下，设定静态工作点。
}

//算得Roll角。算法见文档。 滚转角
float GetRoll(float* pRealVals, float fNorm) {
	float fNormXZ = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[2] * pRealVals[2]);
	float fCos = fNormXZ / fNorm;
	return acos(fCos) * fRad2Deg;
}

//算得Pitch角。算法见文档。 俯仰角
float GetPitch(float* pRealVals, float fNorm) {
	float fNormYZ = sqrt(pRealVals[1] * pRealVals[1] + pRealVals[2] * pRealVals[2]);
	float fCos = fNormYZ / fNorm;
	return acos(fCos) * fRad2Deg;
}
//偏航角
float GetYaw(float* pRealVals, float fNorm)
{
	float fNormXY = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[1] * pRealVals[1]);
	float fCos = fNormXY / fNorm;
	return acos(fCos) * fRad2Deg;

}

//对读数进行纠正，消除偏移，并转换为物理量。公式见文档。
void Rectify(int* pReadout, float* pRealVals) {
	for (int i = 0; i < 3; ++i) {
		pRealVals[i] = (float)(pReadout[i] - calibData[i]) / 16384.0f;
	}
	pRealVals[3] = pReadout[3] / 340.0f + 36.53;
	for (int i = 4; i < 7; ++i) {
		pRealVals[i] = (float)(pReadout[i] - calibData[i]) / 131.0f;
	}
}




void Mpu_Init()
{
	Wire.begin();
	
	Mpu_WriteReg(0x6B, 0); //启动MPU6050设备

	//Calibration(); //执行校准
	Mpu_Lasttime = micros(); //记录当前时间
}

int readouts[Mpu_Valcnt];
float realVals[7];
void Mpu_GetValues() {

	ReadAccGyr(readouts); //读出测量值


	Rectify(readouts, realVals); //根据校准的偏移量进行纠正

	//计算加速度向量的模长，均以g为单位
	float fNorm = sqrt(realVals[0] * realVals[0] + realVals[1] * realVals[1] + realVals[2] * realVals[2]);
	float fRoll =
		GetRoll(realVals, fNorm); //计算Roll角
	if (realVals[1] > 0) {
		fRoll = -fRoll;
	}
	float fPitch = GetPitch(realVals, fNorm); //计算Pitch角
	if (realVals[0] < 0) {
		fPitch = -fPitch;
	}
	float fYaw = GetYaw(realVals, fNorm); //计算Pitch角
	if (realVals[2] < 0) {
		fYaw = -fYaw;//此处需要进一步确定
	}
   //计算两次测量的时间间隔dt，以秒为单位
		unsigned long nCurTime = micros();
		float dt = (double)(nCurTime - Mpu_Lasttime) / 1000000.0;
		//对Roll角和Pitch角进行卡尔曼滤波
		float fNewRoll = kalmanRoll.getAngle(fRoll, realVals[4], dt);
		float fNewPitch = kalmanPitch.getAngle(fPitch, realVals[5], dt);
		float fNewYaw = kalmanYaw.getAngle(fYaw, realVals[6], dt);
		//跟据滤波值计算角度速
		Mpu_RollRate = (fNewRoll - Mpu_Roll) / dt;
		Mpu_PitchRate = (fNewPitch - Mpu_Pitch) / dt;
		Mpu_YawRate = -(fNewYaw - Mpu_Yaw) / dt;
		//更新Roll角和Pitch角
		Mpu_Roll = fNewRoll;
		Mpu_Pitch = fNewPitch;
		Mpu_Yaw = fNewYaw;
		//更新本次测的时间
		Mpu_Lasttime = nCurTime;


	}

	void Mpu_ShowValuesOnSerial()
	{
		Serial.print("Roll:");
		Serial.print(Mpu_Roll); Serial.print('(');
		Serial.print(Mpu_RollRate); Serial.print("),\tPitch:");
		Serial.print(Mpu_Yaw); Serial.print('(');
		Serial.print(Mpu_YawRate); Serial.print(")\n");
		delay(10);
		
	}


