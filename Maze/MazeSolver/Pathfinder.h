#pragma once


#include "Tile.h"

#include <vector>


class Pathfinder
{
public:
	std::vector<Dir> FindPath(Tile *start, Tile *end);

private:
	virtual std::vector<Dir> DoFindPath(Tile *start, Tile *end) = 0;
};