#include "MicroMove.h"
#include "IncludeList.h"

void MicroMove_Init ()
{
	pinMode (MicroMove_Pin, INPUT);
	pinMode (MicroMove_Pin2, INPUT);
	pinMode (MicroMove_Pin3, INPUT);
	pinMode (MicroMove_Pin4, INPUT);

}
bool MicroMove_IsPushed (int opt)
{
	if(opt == 1)return !digitalRead (MicroMove_Pin);
	if (opt == 2)return !digitalRead (MicroMove_Pin2);
	if (opt == 3)return !digitalRead (MicroMove_Pin3);
	if (opt == 4)return !digitalRead (MicroMove_Pin4);


}