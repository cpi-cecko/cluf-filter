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

Tile* Tile::GetUpTile() const
{
	if (pos.y <= 0)
		return NULL;

	return &owner->map[pos.x][pos.y-1];
}
Tile* Tile::GetDownTile() const
{
	if (pos.y >= owner->GetRows())
		return NULL;

	return &owner->map[pos.x][pos.y+1];
}
Tile* Tile::GetRightTile() const
{
	if (pos.x <= 0)
		return NULL;

	return &owner->map[pos.x-1][pos.y];
}
Tile* Tile::GetLeftTile() const
{
	if (pos.x >= owner->GetCols())
		return NULL;

	return &owner->map[pos.x+1][pos.y];
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

void Tile::SetVisited(bool newIsVisited)
{
	isVisited = newIsVisited;
}

void Tile::SetDir(Dir newDir)
{
	dir = newDir;
}