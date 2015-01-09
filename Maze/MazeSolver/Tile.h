#pragma once


enum DIRS
{
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_DOWN,

	DIR_COUNT
};

struct Position
{
	int x;
	int y;

	Position()
		: x(), y()
	{
	}

	Position(int newX, int newY)
		: x(newX), y(newY)
	{
	}
};

class Map;

class Tile
{
private:
	Position pos;
	char symbol;
	Map *owner;

public:
	void SetOwner(Map *newOwner);
	char GetSymbol() const;

	bool IsExit() const;
	bool IsStart() const;
	bool IsEmpty() const;
	bool IsBlock() const;

	Tile();
	Tile(const Position &newPos, char newSymbol);

	friend class Map;
};