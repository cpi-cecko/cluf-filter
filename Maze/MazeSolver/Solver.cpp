#include "stdafx.h"
#include "Solver.h"

#include "Map.h"
#include "BFSPathfinder.h"

#include <iostream>


static void PrintPath(const std::vector<Dir> &path);

void Solver::SolveMaze(Map *mazeMap)
{
	Pathfinder *bfsFinder = new BFSPathfinder();
	std::vector<Dir> path = bfsFinder->FindPath(mazeMap->GetStartTile(), mazeMap->GetExitTile());
	std::vector<Tile*> doors = mazeMap->GetDoorTiles();

	PrintPath(path);
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