#include "stdafx.h"
#include "Tile.h"

#include "Map.h"


const char TILE_BLOCK = '#';
const char TILE_EMPTY = ' ';
const char TILE_START = 'S';
const char TILE_EXIT = 'X';


Tile::Tile()
	: pos(), symbol('\0'), owner(NULL)
{
}

Tile::Tile(const Position &newPos, char newSymbol)
	: pos(newPos), symbol(newSymbol), owner(NULL)
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