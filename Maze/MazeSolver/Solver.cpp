#include "stdafx.h"
#include "Solver.h"

#include "Map.h"
#include "BFSPathfinder.h"

#include <iostream>
#include <algorithm>


static void PrintPath(const PathInfo &path);

void Solver::SolveMaze(Map *mazeMap)
{
	//FindPathsToDoors(mazeMap);

	//for (size_t idx = 0; idx < pathsToDoors.size(); ++idx)
	//{
	//	PrintPath(pathsToDoors[idx]);
	//}

	Pathfinder *bfsFinder = new BFSPathfinder();

	PathInfo path = bfsFinder->FindPath(mazeMap->GetStartTile(), mazeMap->GetExitTile());

	if ( ! path.path.empty())
	{
		PrintPath(path);
	}
}

void Solver::FindPathsToDoors(Map *mazeMap)
{
	Pathfinder *bfsFinder = new BFSPathfinder();

	std::vector<std::pair<Tile*, Tile*>> keyDoorPairs = mazeMap->GetKeyDoorPairs();
	Tile *start = mazeMap->GetStartTile();
	Tile *end = mazeMap->GetExitTile();

	for (size_t idx = 0; idx < keyDoorPairs.size(); ++idx)
	{
		mazeMap->UnsetTilesVisited();
		PathInfo startToDoor = bfsFinder->FindPath(start, keyDoorPairs[idx].first);
		if (startToDoor.path.empty())
		{
			break;
		}
		mazeMap->UnsetTilesVisited();
		PathInfo keyToDoor = bfsFinder->FindPath(keyDoorPairs[idx].first, keyDoorPairs[idx].second);
		if (keyToDoor.path.empty())
		{
			break;
		}
		pathsToDoors.push_back(startToDoor);
		pathsToDoors.push_back(keyToDoor);
	}

	pathsToDoors.erase(std::remove_if(pathsToDoors.begin(), pathsToDoors.end(), 
					   [](PathInfo info) {return info.path.empty();}), pathsToDoors.end());






	//for (size_t idx = 0; idx < doors.size(); ++idx)
	//{
	//	mazeMap->UnsetTilesVisited();
	//	found = bfsFinder->FindPath(start, doors[idx]);
	//	pathsToDoors.push_back(found);
	//	mazeMap->UnsetTilesVisited();
	//	found = bfsFinder->FindPath(doors[idx], end);
	//	pathsToDoors.push_back(found);
	//}

	//for (size_t idx = 0; idx < doors.size(); ++idx)
	//{
	//	for (size_t idx2 = idx + 1; idx2 < doors.size(); ++idx2)
	//	{
	//		mazeMap->UnsetTilesVisited();
	//		found = bfsFinder->FindPath(doors[idx], doors[idx2]);
	//		pathsToDoors.push_back(found);
	//	}
	//}

	//mazeMap->UnsetTilesVisited();
	//found = bfsFinder->FindPath(start, end);
	//pathsToDoors.push_back(found);

	// auto keyPairs = mazeMap->GetKeyDoorPairs();
	// for (size_t idx = 0; idx < keyPairs.size(); ++idx)
	// {
	// 	mazeMap->UnsetTilesVisited();
	//	mazeMap->UnlockDoors(); // We want to find key-door paths regardless of locking
	// 	found = bfsFinder->FindPath(keyPairs[idx].first, keyPairs[idx].second);
	// 	pathsToDoors.push_back(found);
	// }

	//pathsToDoors.erase(std::remove_if(pathsToDoors.begin(), pathsToDoors.end(), 
	//				   [](PathInfo info) {return info.path.empty();}), pathsToDoors.end());
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