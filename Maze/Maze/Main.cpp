#include <iostream>

#include "../MazeSolver/Map.h"
#include "../MazeSolver/Solver.h"


int main()
{
	Map newMap;
	newMap.LoadMap("lab7.txt");
	newMap.DebugPrintMap();

	Solver newSolver;
	newSolver.SolveMaze(&newMap);

	return 0;
}