#pragma once


#include "Pathfinder.h"


class BFSPathfinder : public Pathfinder
{
private:
	virtual Dir* DoFindPath(const Map *inMap, const Tile *start, const Tile *end);
};