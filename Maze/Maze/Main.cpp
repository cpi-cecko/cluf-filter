#include <iostream>

#include "../MazeSolver/Map.h"
#include "../MazeSolver/BFSPathfinder.h"


int main()
{
	Map newMap;
	newMap.LoadMap("lab1.txt");
	newMap.DebugPrintMap();

	Pathfinder *bfsFinder = new BFSPathfinder();
	bfsFinder->FindPath(&newMap, newMap.GetStartTile(), newMap.GetExitTile());

	return 0;
}