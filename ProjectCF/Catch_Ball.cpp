#include "Catch_Ball.h"


int CB_RiseArm (int angle) {
	Arm_Init ();
	Arm_Go (1, 30);
	return 0;
}
int CB_CloseClaw (int angle) {
	Arm_Reset (2);
	Arm_Go (2, 30);
}