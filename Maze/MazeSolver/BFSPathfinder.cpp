#include "stdafx.h"
#include "BFSPathfinder.h"

#include <iostream>
#include <stack>


static Dir GetDir(Tile *current, Tile *neighbour);

static Tile* GetCurrentTileByIdx(size_t idx, Tile *parent);


PathInfo BFSPathfinder::DoFindPath(Tile *start, Tile *end)
{
	std::vector<Tile*> bestNeighbourForNode = CalculateBestNeighbours(start, end);

	std::list<Tile*> reduced = GetDoorsFromPath(start, end, bestNeighbourForNode);
	reduced.push_front(start);
	while ( ! reduced.empty())
	{
		std::list<Tile*>::iterator doorToCheck;
		for (doorToCheck = reduced.begin(); doorToCheck != reduced.end(); ++doorToCheck)
		{
			if ((*doorToCheck)->IsDoor() && (*doorToCheck)->IsLockedDoor())
			{
				break;
			}
		}

		if (doorToCheck == reduced.end())
		{
			break;
		}

		Tile *keyForDoor = (*doorToCheck)->GetKeyForThisDoor();
		auto bestNeighbours = CalculateBestNeighbours(start, keyForDoor);
		auto path = GetDoorsFromPath(start, keyForDoor, bestNeighbours);
		if (std::find(path.begin(), path.end(), (*doorToCheck)) != path.end())
		{
			// To reach the door's key, we have to pass through the door
			return PathInfo();
		}
		if ( ! path.empty())
		{
			reduced.insert(doorToCheck, path.begin(), path.end());
		}
		reduced.insert(doorToCheck, keyForDoor);
	}
	reduced.push_back(end);

	PathInfo path;
	path.start = start;
	path.end = end;
	while (reduced.size() > 1)
	{
		Tile *first = reduced.front();
		reduced.pop_front();
		Tile *second = reduced.front();
		if (first->GetSymbol() == second->GetSymbol())
		{
			reduced.pop_front();
			second = reduced.front();
		}

		auto best = CalculateBestNeighbours(first, second);
		auto currentPath = GetPathFromBestNeighbours(first, second, best).path;
		path.path.insert(path.path.end(), currentPath.begin(), currentPath.end());
	}

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

std::list<Tile*> BFSPathfinder::GetDoorsFromPath(Tile *start, Tile *end,
												 const std::vector<Tile*> &bestNeighbours)
{
	if (bestNeighbours.empty())
		return std::list<Tile*>();

	std::list<Tile*> doors;
	Tile *current = end;

	while (current != start)
	{
		Tile *bestNeighbour = bestNeighbours[current->GetTileIdx()];
		if (bestNeighbour)
		{
			if (current->IsDoor())
			{
				doors.push_back(current);
			}
			current = bestNeighbour;
		}
		else return std::list<Tile*>();
	}
	std::reverse(doors.begin(), doors.end());
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
			if (bestDir != DIR_INVALID)
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
	return DIR_INVALID;
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