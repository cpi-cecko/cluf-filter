#pragma once


#include "Tile.h"

#include <vector>
#include "PathInfo.h"


class Pathfinder
{
public:
	PathInfo FindPath(Tile *start, Tile *end);

private:
	virtual PathInfo DoFindPath(Tile *start, Tile *end) = 0;
};