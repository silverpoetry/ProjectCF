
#pragma once
enum Mpu_dir
{
	Left = -1, Right = 1
};
extern float Mpu_Angles[3];
void Mpu_Init();
void Mpu_ReadData();
void Mpu_ReadData2();
void Mpu_GoAngle(float angle, Mpu_dir dir);
void Mpu_GoRelativeAngle(int angel);
void Mpu_ResetZ();
void Mpu_RecordAngle();
void Mpu_AdjustStraight(int speed);
void Mpu_GoRelativeAngleSetSpeed (int angel, int speed1, int speed2);
void Mpu_GoRelativeAngleAAA (int angel);
