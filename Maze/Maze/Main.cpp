#include <iostream>

#include "../MazeSolver/Map.h"
#include "../MazeSolver/Solver.h"


void RunTests();

int main()
{
	Map newMap;
	newMap.LoadMap("lab8.txt");
	newMap.DebugPrintMap();

	Solver newSolver;
	newSolver.SolveMaze(&newMap);

	return 0;
}