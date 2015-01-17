#include "stdafx.h"
#include "Pathfinder.h"


#include <iostream>


PathInfo Pathfinder::FindPath(Tile *start, Tile *end)
{
	if ( ! start || ! end)
	{
		std::cerr << "Null pointer to FindPath\n";
		return PathInfo();
	}

	return DoFindPath(start, end);
}