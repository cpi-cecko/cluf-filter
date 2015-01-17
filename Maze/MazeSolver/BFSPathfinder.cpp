#include "stdafx.h"
#include "BFSPathfinder.h"

#include <iostream>


static Dir GetDir(Tile *current, Tile *neighbour);

PathInfo BFSPathfinder::DoFindPath(Tile *start, Tile *end)
{
	while ( ! walkedTiles.empty())
	{
		walkedTiles.pop();
	}

	Tile *current = NULL;
	walkedTiles.push(start);

	path.clear();
	bestNeighbourForNode.resize(start->GetMazeSize());

	while ( ! walkedTiles.empty())
	{
		current = walkedTiles.front();
		current->SetVisited(true);
		walkedTiles.pop();
		
		if (current == end)
		{
			while (current != start)
			{
				Tile *bestNeighbour = bestNeighbourForNode[current->GetTileIdx()];
				Dir bestDir = GetDir(current, bestNeighbour);
				if (bestDir != DIR_COUNT)
				{
					path.push_back(bestDir);
				}
				current = bestNeighbour;
			}
			std::reverse(path.begin(), path.end());
			return PathInfo(path, start, end);
		}
		else
		{
			AddIfPassable(current->GetUpTile(), current, end);
			AddIfPassable(current->GetDownTile(), current, end);
			AddIfPassable(current->GetLeftTile(), current, end);
			AddIfPassable(current->GetRightTile(), current, end);
		}
	}

	return PathInfo();
}

static Dir GetDir(Tile *current, Tile *neighbour)
{
	if (current->GetLeftTile() == neighbour)
	{
		return DIR_RIGHT;
	}
	else if (current->GetRightTile() == neighbour)
	{
		return DIR_LEFT;
	}
	else if (current->GetUpTile() == neighbour)
	{
		return DIR_DOWN;
	}
	else if (current->GetDownTile() == neighbour)
	{
		return DIR_UP;
	}
	return DIR_COUNT;
}

void BFSPathfinder::AddIfPassable(Tile *currentTile, Tile *parent, Tile *end)
{
	if (currentTile && (currentTile == end || ! currentTile->IsDoor()) && 
		currentTile->IsWalkable() && ! currentTile->IsVisited())
	{
		currentTile->SetVisited(true);
		walkedTiles.push(currentTile);
		bestNeighbourForNode[currentTile->GetTileIdx()] = parent;
	}
}