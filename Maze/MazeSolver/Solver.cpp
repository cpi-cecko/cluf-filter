#include "stdafx.h"
#include "Solver.h"

#include "Map.h"
#include "BFSPathfinder.h"

#include <iostream>


static void PrintPath(const std::vector<Dir> &path);

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

	for (size_t idx = 0; idx < doors.size(); ++idx)
	{
		mazeMap->UnsetTilesVisited();
		pathsToDoors.push_back(bfsFinder->FindPath(start, doors[idx]));
		mazeMap->UnsetTilesVisited();
		pathsToDoors.push_back(bfsFinder->FindPath(doors[idx], end));
	}

	for (size_t idx = 0; idx < doors.size(); ++idx)
	{
		for (size_t idx2 = idx + 1; idx2 < doors.size(); ++idx2)
		{
			mazeMap->UnsetTilesVisited();
			pathsToDoors.push_back(bfsFinder->FindPath(doors[idx], doors[idx2]));
		}
	}

	mazeMap->UnsetTilesVisited();
	pathsToDoors.push_back(bfsFinder->FindPath(start, end));

	pathsToDoors.erase(std::remove_if(pathsToDoors.begin(), pathsToDoors.end(), 
					   [](std::vector<Dir> path) {return path.empty();}), pathsToDoors.end());
}

static void PrintPath(const std::vector<Dir> &path)
{
	for (auto dirIt = path.begin(); dirIt != path.end(); ++dirIt)
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