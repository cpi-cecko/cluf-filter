#include "stdafx.h"
#include "Pathfinder.h"


#include <iostream>


std::vector<Dir> Pathfinder::FindPath(Tile *start, Tile *end)
{
	if ( ! start || ! end)
	{
		std::cerr << "Null pointer to FindPath\n";
		return std::vector<Dir>();
	}

	return DoFindPath(start, end);
}