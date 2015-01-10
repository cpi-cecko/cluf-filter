#pragma once


#include "Tile.h"

class Pathfinder
{
public:
	Dir* FindPath(const Map *inMap, const Tile *start, const Tile *end);

private:
	virtual Dir* DoFindPath(const Map *inMap, const Tile *start, const Tile *end) = 0;
};