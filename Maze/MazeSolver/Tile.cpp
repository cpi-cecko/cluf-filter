#include "stdafx.h"
#include "Tile.h"

#include "Map.h"


const char TILE_BLOCK = '#';
const char TILE_EMPTY = ' ';
const char TILE_START = 'S';
const char TILE_EXIT = 'E';


Tile::Tile()
	: pos(), symbol('\0'), owner(NULL), dir(DIR_COUNT), isVisited(false)
{
}

Tile::Tile(const Position &newPos, char newSymbol)
	: pos(newPos), symbol(newSymbol), owner(NULL), dir(DIR_COUNT), isVisited(false)
{
}

void Tile::SetOwner(Map *newOwner)
{
	owner = newOwner;
}

char Tile::GetSymbol() const
{
	return symbol;
}

void Tile::ClearVisitedForOwner()
{
	owner->UnsetTilesVisited();
}

int Tile::GetMazeSize() const
{
	return owner->GetCols() * owner->GetRows();
}
int Tile::GetTileIdx() const
{
	return pos.col + pos.row * owner->GetCols();
}

Tile* Tile::GetUpTile() const
{
	if (pos.row <= 0)
		return NULL;

	return &owner->map[pos.row - 1][pos.col];
}
Tile* Tile::GetDownTile() const
{
	if (pos.row >= owner->GetRows() - 1)
		return NULL;

	return &owner->map[pos.row + 1][pos.col];
}
Tile* Tile::GetRightTile() const
{
	if (pos.col >= owner->GetCols() - 1)
		return NULL;

	return &owner->map[pos.row][pos.col + 1];
}
Tile* Tile::GetLeftTile() const
{
	if (pos.col <= 0)
		return NULL;

	return &owner->map[pos.row][pos.col - 1];
}
Tile* Tile::GetKeyForThisDoor() const
{
	return owner->GetKeyForDoor(symbol);
}

Tile* Tile::GetDoorForThisKey() const
{
	return owner->GetDoorForKey(symbol);
}

Dir Tile::GetDir() const
{
	return dir;
}

bool Tile::IsExit() const
{
	return symbol == TILE_EXIT;
}
bool Tile::IsStart() const
{
	return symbol == TILE_START;
}
bool Tile::IsEmpty() const
{
	return symbol == TILE_EMPTY;
}
bool Tile::IsBlock() const
{
	return symbol == TILE_BLOCK;
}
bool Tile::IsWalkable() const
{
	return ! IsBlock();
}
bool Tile::IsVisited() const
{
	return isVisited;
}
bool Tile::IsKey() const
{
	return owner->IsKey(symbol);
}
bool Tile::IsDoor() const
{
	return owner->IsDoor(symbol);
}
bool Tile::IsLockedDoor() const
{
	return owner->IsDoorLocked(symbol);
}
bool Tile::IsKeyRetrieved() const
{
	return owner->IsKeyRetrieved(symbol);
}

void Tile::SetVisited(bool newIsVisited)
{
	isVisited = newIsVisited;
}

void Tile::SetDir(Dir newDir)
{
	dir = newDir;
}

void Tile::Unlock()
{
	owner->UnlockDoor(symbol);
}

void Tile::MarkKeyRetrieved()
{
	owner->UnlockDoorWithKey(symbol);
}

Tile::Tile(const Tile &other)
{
	CopyFrom(other);
}

Tile& Tile::operator=(const Tile &other)
{
	if (this == &other)
	{
		return *this;
	}

	CopyFrom(other);
	return *this;
}

void Tile::CopyFrom(const Tile &other)
{
	pos = other.pos;
	symbol = other.symbol;
	owner = other.owner;
	isVisited = other.isVisited;
	dir = other.dir;
}