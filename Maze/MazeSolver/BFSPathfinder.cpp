#include "stdafx.h"
#include "BFSPathfinder.h"

#include <iostream>
#include <stack>


static Dir GetDir(Tile *current, Tile *neighbour);

static Tile* GetCurrentTileByIdx(size_t idx, Tile *parent);


PathInfo BFSPathfinder::DoFindPath(Tile *start, Tile *end)
{
	std::vector<Tile*> bestNeighbourForNode = CalculateBestNeighbours(start, end);

	std::vector<Tile*> reduced = GetDoorsFromPath(start, end, bestNeighbourForNode);
	std::vector<Tile*> updatedReduced;
	if ( ! reduced.empty())
	{
		for (size_t idx = 1; idx < reduced.size(); ++idx)
		{
			if ( ! reduced[idx]->IsDoor() || ! reduced[idx]->IsLockedDoor())
			{
				updatedReduced.push_back(reduced[idx]);
				continue;
			}

			Tile *doorKey = reduced[idx]->GetKeyForThisDoor();
			auto newBestNeighbours = CalculateBestNeighbours(reduced[idx-1], doorKey);
			auto reducedPathToKey = GetDoorsFromPath(reduced[idx-1], doorKey, newBestNeighbours);
			if ( ! reducedPathToKey.empty())
			{
				reduced[idx]->Unlock();
				updatedReduced.insert(updatedReduced.end(), 
									  reducedPathToKey.begin(), reducedPathToKey.end());
			}
		}
	}

	PathInfo path = GetPathFromBestNeighbours(start, end, bestNeighbourForNode);

	return path;
}

std::vector<Tile*> BFSPathfinder::CalculateBestNeighbours(Tile *start, Tile *end)
{
	std::stack<Tile*> walkedTiles;
	std::vector<Tile*> visitedTiles;

	Tile *current = NULL;
	walkedTiles.push(start);

	std::vector<Tile*> bestNeighbourForNode;
	bestNeighbourForNode.resize(start->GetMazeSize());

	while ( ! walkedTiles.empty())
	{
		current = walkedTiles.top();
		visitedTiles.push_back(current);
		walkedTiles.pop();
		
		if (current == end)
		{
			if (current->IsKey())
			{
				current->MarkKeyRetrieved();
			}
			break;
		}
		else
		{
			for (size_t i = 0; i < 4; ++i)
			{
				Tile *nextTile = GetCurrentTileByIdx(i, current);
				
				if (nextTile && nextTile->IsWalkable() && 
					std::find(visitedTiles.begin(), visitedTiles.end(), nextTile) == visitedTiles.end())
				{
					visitedTiles.push_back(nextTile);
					walkedTiles.push(nextTile);
					bestNeighbourForNode[nextTile->GetTileIdx()] = current;
				}
			}
		}
	}

	return bestNeighbourForNode;
}

std::vector<Tile*> BFSPathfinder::GetDoorsFromPath(Tile *start, Tile *end,
												   const std::vector<Tile*> &bestNeighbours)
{
	if (bestNeighbours.empty())
		return std::vector<Tile*>();

	std::vector<Tile*> doors;
	Tile *current = end;

	while (current != start)
	{
		Tile *bestNeighbour = bestNeighbours[current->GetTileIdx()];
		if (bestNeighbour)
		{
			if (current->IsDoor() )
			{
				doors.push_back(current);
			}
			current = bestNeighbour;
		}
		else return std::vector<Tile*>();
	}

	return doors;
}

PathInfo BFSPathfinder::GetPathFromBestNeighbours(Tile *start, Tile *end, 
												  const std::vector<Tile*> &bestNeighbours)
{
	if (bestNeighbours.empty())
		return PathInfo();

	std::vector<Dir> path;
	Tile *current = end;

	while (current != start)
	{
		Tile *bestNeighbour = bestNeighbours[current->GetTileIdx()];
		if (bestNeighbour)
		{
			Dir bestDir = GetDir(current, bestNeighbour);
			if (bestDir != DIR_COUNT)
			{
				path.push_back(bestDir);
			}
			current = bestNeighbour;
		}
		else return PathInfo();
	}
	std::reverse(path.begin(), path.end());
	return PathInfo(path, start, end);
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

static Tile* GetCurrentTileByIdx(size_t idx, Tile *parent)
{
	switch (idx)
	{
	case 0:
		return parent->GetUpTile();
	case 1:
		return parent->GetDownTile();
	case 2:
		return parent->GetLeftTile();
	case 3:
		return parent->GetRightTile();
	default:
		std::cerr << "Bad index '" << idx << "' for current tile\n";
		return NULL;
	};
}