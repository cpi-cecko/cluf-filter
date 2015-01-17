#include "stdafx.h"
#include "Solver.h"

#include "Map.h"
#include "BFSPathfinder.h"

#include <iostream>


static void PrintPath(const PathInfo &path);

void Solver::SolveMaze(Map *mazeMap)
{
	FindPathsToDoors(mazeMap);

	for (size_t idx = 0; idx < pathsToDoors.size(); ++idx)
	{
		PrintPath(pathsToDoors[idx]);
	}
}

void Solver::FindPathsToDoors(Map *mazeMap)
{
	Pathfinder *bfsFinder = new BFSPathfinder();

	std::vector<Tile*> doors = mazeMap->GetDoorTiles();
	Tile *start = mazeMap->GetStartTile();
	Tile *end = mazeMap->GetExitTile();

	PathInfo found;
	for (size_t idx = 0; idx < doors.size(); ++idx)
	{
		mazeMap->UnsetTilesVisited();
		found.path = bfsFinder->FindPath(start, doors[idx]);
		found.start = start;
		found.end = doors[idx];
		pathsToDoors.push_back(found);
		mazeMap->UnsetTilesVisited();
		found.path = bfsFinder->FindPath(doors[idx], end);
		found.start = doors[idx];
		found.end = end;
		pathsToDoors.push_back(found);
	}

	for (size_t idx = 0; idx < doors.size(); ++idx)
	{
		for (size_t idx2 = idx + 1; idx2 < doors.size(); ++idx2)
		{
			mazeMap->UnsetTilesVisited();
			found.path = bfsFinder->FindPath(doors[idx], doors[idx2]);
			found.start = doors[idx];
			found.end = doors[idx2];
			pathsToDoors.push_back(found);
		}
	}

	mazeMap->UnsetTilesVisited();
	found.path = bfsFinder->FindPath(start, end);
	found.start = start;
	found.end = end;
	pathsToDoors.push_back(found);

	pathsToDoors.erase(std::remove_if(pathsToDoors.begin(), pathsToDoors.end(), 
					   [](PathInfo info) {return info.path.empty();}), pathsToDoors.end());
}

static void PrintPath(const PathInfo &info)
{
	std::cout << "(" << info.start->GetSymbol() << ", " << info.end->GetSymbol() << ") ";
	for (auto dirIt = info.path.begin(); dirIt != info.path.end(); ++dirIt)
	{
		switch ((*dirIt))
		{
		case DIR_UP:
			std::cout << "U";
			break;
		case DIR_DOWN:
			std::cout << "D";
			break;
		case DIR_RIGHT:
			std::cout << "R";
			break;
		case DIR_LEFT:
			std::cout << "L";
			break;
		default:
			std::cerr << "Invalid direction\n";
			break;
		}
	}
	std::cout << std::endl;
}