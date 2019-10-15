#include "Mpu.h"
#include "IncludeList.h"
#include <Kalman.h>
#include <Wire.h>
#include <Math.h>

float fRad2Deg = 57.295779513f; //������תΪ�Ƕȵĳ���
#define MPU_ADDR  0x68 //MPU-6050��I2C��ַ
const int Mpu_Valcnt = 7; //һ�ζ�ȡ�Ĵ���������

float Mpu_Roll = 0.0f; //��һ���˲��õ���Roll��
float Mpu_Pitch = 0.0f; //��һ���˲��õ���Pitch��
float Mpu_RollRate = 0.0f;
float Mpu_PitchRate = 0.0f;
float Mpu_Yaw = 0.0f;
float Mpu_YawRate = 0.0f;


const int nCalibTimes = 1000; //У׼ʱ�����Ĵ���
int calibData[Mpu_Valcnt]; //У׼����




unsigned long Mpu_Lasttime = 0; //��һ�ζ�����ʱ��

Kalman kalmanRoll; //Roll���˲���
Kalman kalmanPitch; //Pitch���˲���
Kalman kalmanYaw;

//��MPU6050д��һ���ֽڵ�����
//ָ���Ĵ�����ַ��һ���ֽڵ�ֵ
void Mpu_WriteReg(int nReg, unsigned char nVal) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(nReg);
	Wire.write(nVal);
	Wire.endTransmission(true);
}

//��MPU6050����һ���ֽڵ�����
//ָ���Ĵ�����ַ�����ض�����ֵ
unsigned char Mpu_ReadReg(int nReg) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(nReg);
	Wire.requestFrom(MPU_ADDR, 1, true);
	Wire.endTransmission(true);
	return Wire.read();
}

//��MPU6050�������ٶȼ������������¶Ⱥ��������ٶȼ�
//������ָ����������
void ReadAccGyr(int* pVals) {
	Wire.beginTransmission(MPU_ADDR);
	Wire.write(0x3B);
	Wire.requestFrom(MPU_ADDR, Mpu_Valcnt * 2, true);
	Wire.endTransmission(true);
	for (long i = 0; i < Mpu_Valcnt; ++i) {
		pVals[i] = Wire.read() << 8 | Wire.read();
	}
}


//�Դ�����������ͳ�ƣ�У׼ƽ��ƫ����
void Calibration()
{
	float valSums[7] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0 };
	//�����
	for (int i = 0; i < nCalibTimes; ++i) {
		int mpuVals[Mpu_Valcnt];
		
		ReadAccGyr(mpuVals);
		for (int j = 0; j < Mpu_Valcnt; ++j) {
			valSums[j] += mpuVals[j];
		}
	}
	//����ƽ��
	for (int i = 0; i < Mpu_Valcnt; ++i) {
		calibData[i] = int(valSums[i] / nCalibTimes);
	}

	//calibData[2] += 16384; //��оƬZ����ֱ���£��趨��̬�����㡣
}

//���Roll�ǡ��㷨���ĵ��� ��ת��
float GetRoll(float* pRealVals, float fNorm) {
	float fNormXZ = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[2] * pRealVals[2]);
	float fCos = fNormXZ / fNorm;
	return acos(fCos) * fRad2Deg;
}

//���Pitch�ǡ��㷨���ĵ��� ������
float GetPitch(float* pRealVals, float fNorm) {
	float fNormYZ = sqrt(pRealVals[1] * pRealVals[1] + pRealVals[2] * pRealVals[2]);
	float fCos = fNormYZ / fNorm;
	return acos(fCos) * fRad2Deg;
}
//ƫ����
float GetYaw(float* pRealVals, float fNorm)
{
	float fNormXY = sqrt(pRealVals[0] * pRealVals[0] + pRealVals[1] * pRealVals[1]);
	float fCos = fNormXY / fNorm;
	return acos(fCos) * fRad2Deg;

}

//�Զ������о���������ƫ�ƣ���ת��Ϊ����������ʽ���ĵ���
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
	
	Mpu_WriteReg(0x6B, 0); //����MPU6050�豸

	//Calibration(); //ִ��У׼
	Mpu_Lasttime = micros(); //��¼��ǰʱ��
}

int readouts[Mpu_Valcnt];
float realVals[7];
void Mpu_GetValues() {

	ReadAccGyr(readouts); //��������ֵ


	Rectify(readouts, realVals); //����У׼��ƫ�������о���

	//������ٶ�������ģ��������gΪ��λ
	float fNorm = sqrt(realVals[0] * realVals[0] + realVals[1] * realVals[1] + realVals[2] * realVals[2]);
	float fRoll =
		GetRoll(realVals, fNorm); //����Roll��
	if (realVals[1] > 0) {
		fRoll = -fRoll;
	}
	float fPitch = GetPitch(realVals, fNorm); //����Pitch��
	if (realVals[0] < 0) {
		fPitch = -fPitch;
	}
	float fYaw = GetYaw(realVals, fNorm); //����Pitch��
	if (realVals[2] < 0) {
		fYaw = -fYaw;//�˴���Ҫ��һ��ȷ��
	}
   //�������β�����ʱ����dt������Ϊ��λ
		unsigned long nCurTime = micros();
		float dt = (double)(nCurTime - Mpu_Lasttime) / 1000000.0;
		//��Roll�Ǻ�Pitch�ǽ��п������˲�
		float fNewRoll = kalmanRoll.getAngle(fRoll, realVals[4], dt);
		float fNewPitch = kalmanPitch.getAngle(fPitch, realVals[5], dt);
		float fNewYaw = kalmanYaw.getAngle(fYaw, realVals[6], dt);
		//�����˲�ֵ����Ƕ���
		Mpu_RollRate = (fNewRoll - Mpu_Roll) / dt;
		Mpu_PitchRate = (fNewPitch - Mpu_Pitch) / dt;
		Mpu_YawRate = -(fNewYaw - Mpu_Yaw) / dt;
		//����Roll�Ǻ�Pitch��
		Mpu_Roll = fNewRoll;
		Mpu_Pitch = fNewPitch;
		Mpu_Yaw = fNewYaw;
		//���±��β��ʱ��
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


