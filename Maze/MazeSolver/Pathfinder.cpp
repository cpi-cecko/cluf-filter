#include "stdafx.h"
#include "Pathfinder.h"


Dir* Pathfinder::FindPath(const Map *inMap, const Tile *start, const Tile *end)
{
	return DoFindPath(inMap, start, end);
}