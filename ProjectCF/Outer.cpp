
bool SavePeopleReadyforEntrance () {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord ());
	if (abs (Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}
bool SavePeopleBackReadytoGoBlind () {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord ());
	if (abs (Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}
bool SavePeopleReturnHome () {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord ());
	if (abs (Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
	return 0;
}

bool EasyMazeReadyforEntrance () {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord ());
	if (abs (Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
}
bool EasyMazeReadyforTurnRight () {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord ());
	if (abs (Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
}
bool EasyMazeGetHome () {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord ());
	if (abs (Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
}

bool GetballReadytoCatch () {
	const int standard_x = 185, standard_y = 0;
	const int eps_x = 2, eps_y = 5;
	while (!Zigbee_MessageRecord ());
	if (abs (Car[0].pos.X - standard_x) < eps_x) {
		return 1;
	}
}

void MainTask_GotoGoods () {
	while (!Manager_Time_TakeTime (12, 500))
	{
		PL_GoBlind (2);
	}
	Move_Stop ();
	while (!MicroMove_IsPushed (1))
	{
		Motor_GoSpeed (0, 150);
	}

	Move_Stop ();
	Motor_GoSpeed (150, 0);
	delay (150);
	while (!MicroMove_IsPushed (1))
	{
		Motor_GoSpeed (150, 150);
	}
	Motor_GoSpeed (100, -50);
	delay (600);
	while (!MicroMove_IsPushed (1))
	{
		Motor_GoSpeed (150, 150);
	}
	//PL_GoBlind (1);
}
void MainTask_CatchBall ();
void MainTask_CollectGoods ()
{
	MainTask_GotoGoods ();
	PL_GoBlind (1);
	while (!GetballReadytoCatch ()) {
		PL_GoBlind (1);
	}
	Move_Stop ();
	MainTask_CatchBall ();
	GetballBack ();
}

void MainTask_GotoPeopleEntrance () {
	while (!Manager_Time_TakeTime (12, 500))
	{
		PL_GoBlind (2);
	}
	Move_Stop ();
	while (!MicroMove_IsPushed (2))
	{
		Motor_GoSpeed (150, 0);
	}

	Move_Stop ();
	Motor_GoSpeed (0, 150);
	delay (150);
	while (!MicroMove_IsPushed (2))
	{
		Motor_GoSpeed (150, 150);
	}
	Motor_GoSpeed (-50, 100);
	delay (600);
	while (!MicroMove_IsPushed (2))
	{
		Motor_GoSpeed (150, 150);
	}

	while (!SavePeopleReadyforEntrance ()) {
		PL_GoBlind (1);
	}
	Move_Gotime (SPEED, SPEED, 300);
	PL_CrossRoad (1);
}
void MainTask_SavePeopleBackHome () {
	while (!MicroMove_IsPushed (2)) {
		Motor_GoSpeed (100, 0);
	}
	while (!SavePeopleBackReadytoGoBlind ()) {
		PL_GoBlind (2);
	}
	Move_Gotime (SPEED, SPEED, 400);
	Move_Gotime (0, SPEED, 1000);
	while (!SavePeopleReturnHome ()) {
		PL_GoBlind (2);
	}
}

void EasyMazeGoEntrance () {
	MainTask_GotoGoods ();
	while (!EasyMazeReadyforEntrance ()) {
		PL_GoBlind (2);
	}
	Move_Gotime (SPEED, SPEED, 400);
	PL_CrossRoad (2);

	/*
	while (!Manager_Time_TakeTime (12, 500))
	{
		PL_GoBlind (1);
	}
	Move_Stop ();
	Move_Gotime (0, 100, 500);
	Move_Gotime (100, 0, 500);
	while (!EasyMazeReadyforEntrance ()) {
		PL_GoBlind (1);
	}
	Move_Gotime (SPEED, SPEED, 300);
	PL_CrossRoad (1);*/
}
void EasyMazeReturnHome () {
	while (!MicroMove_IsPushed (1)) {
		Motor_GoSpeed (0, 100);
	}
	Move_Stop ();
	while (!EasyMazeReadyforTurnRight ()) {
		Motor_GoSpeed (100, 100);
	}
	Move_Gotime (120, 0, 2000);
	while (!EasyMazeGetHome ()) {
		PL_GoBlind (2);
	}
	return;
}


void MainTask_EasyExploreMaze () {

	EasyMazeGoEntrance ();
	car.Position = { 0, 5 };
	Pos exit = { 5, 0 };
	car.Orientation = 3;
	MainTask_Go (car.Position, exit);
	EasyMazeReturnHome ();

}
void MainTask_SavePeople () {
	MainTask_GotoPeopleEntrance ();
	int i = 1;

	car.Position = { 7, 2 };
	Pos exit = { 2, 7 };
	car.Orientation = 1;
	while (i <= 3) {
		while (!Zigbee_MessageRecord ());
		Pos person1 = PsitionConverter (Passenger[0]), person2 = PsitionConverter (Passenger[1]);
		if (MainTask_CntManhattonDist (car.Position, person1) < MainTask_CntManhattonDist (car.Position, person2)) {
			MainTask_Go (car.Position, person1);
		}
		else {
			MainTask_Go (car.Position, person2);
		}
		i++;
	}
	MainTask_Go (car.Position, exit);
	MainTask_SavePeopleBackHome ();
}