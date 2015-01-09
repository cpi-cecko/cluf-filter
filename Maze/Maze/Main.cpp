#include <iostream>

#include "../MazeSolver/Map.h"


int main()
{
	Map newMap;
	newMap.LoadMap("lab1.txt");
	newMap.DebugPrintMap();

	return 0;
}