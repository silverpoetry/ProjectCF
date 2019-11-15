#pragma once
struct Pos {
	int X = -1, Y = -1;
	Pos(int x = 0, int y = 0) {
		this->X = x;
		this->Y = y;
	}
	bool operator ==(const Pos& p)
	{
		return X == p.X&&Y == p.Y;
	}

};
