#pragma once


enum Dir
{
	DIR_LEFT,
	DIR_UP,
	DIR_RIGHT,
	DIR_DOWN,

	DIR_COUNT
};

struct Position
{
	int row;
	int col;

	Position()
		: row(), col()
	{
	}

	Position(int newRow, int newCol)
		: row(newRow), col(newCol)
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
	bool isVisited;
	Dir dir;

public:
	void SetOwner(Map *newOwner);
	char GetSymbol() const;

	void ClearVisitedForOwner();

	Tile* GetUpTile() const;
	Tile* GetDownTile() const;
	Tile* GetRightTile() const;
	Tile* GetLeftTile() const;
	Tile* GetKeyForThisDoor() const;
	Tile* GetDoorForThisKey() const;

	int GetMazeSize() const;
	int GetTileIdx() const;

	Dir GetDir() const;

	bool IsExit() const;
	bool IsStart() const;
	bool IsEmpty() const;
	bool IsBlock() const;
	bool IsWalkable() const;
	bool IsVisited() const;
	bool IsKey() const;
	bool IsDoor() const;
	bool IsLockedDoor() const;
	bool IsKeyRetrieved() const;

	void SetVisited(bool newIsVisited);
	void SetDir(Dir newDir);
	void Unlock();
	void MarkKeyRetrieved();

	Tile();
	Tile(const Position &newPos, char newSymbol);

	Tile(const Tile &other);
	Tile& operator=(const Tile &other);

private:
	void CopyFrom(const Tile &other);

	friend class Map;
};