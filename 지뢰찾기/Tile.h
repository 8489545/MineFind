#pragma once
enum State
{
	MINE = -1,
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EGHIT,
	CURSOR,
	FLAG
};
class Tile
{
public:
	Tile() : isOpen(false) {};
	Tile(int _state);
	~Tile();

	bool isOpen;
	int state;
};

