#include "stdafx.h"
#include "BFSPathfinder.h"

#include <iostream>


std::vector<Dir> BFSPathfinder::DoFindPath(Tile *start, Tile *end)
{
	while ( ! walkedTiles.empty())
	{
		walkedTiles.pop();
	}

	Tile *current = NULL;
	walkedTiles.push(start);

	while ( ! walkedTiles.empty())
	{
		current = walkedTiles.front();
		current->SetVisited(true);
		if (current->GetDir() != DIR_COUNT)
		{
			path.push_back(current->GetDir());
		}
		walkedTiles.pop();
		
		if (current == end)
		{
			return path;
		}
		else
		{
			AddIfPassable(current->GetUpTile(), DIR_UP);
			AddIfPassable(current->GetDownTile(), DIR_DOWN);
			AddIfPassable(current->GetLeftTile(), DIR_LEFT);
			AddIfPassable(current->GetRightTile(), DIR_RIGHT);
		}
	}

	return path;
}

void BFSPathfinder::AddIfPassable(Tile *currentTile, Dir dir)
{
	if (currentTile && currentTile->IsWalkable() && ! currentTile->IsVisited())
	{
		currentTile->SetVisited(true);
		currentTile->SetDir(dir);
		walkedTiles.push(currentTile);
	}
}