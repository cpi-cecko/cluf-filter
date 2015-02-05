#include <iostream>

#include "../MazeSolver/Map.h"
#include "../MazeSolver/Solver.h"

#include "Tests.h"


void RunTests();

int main()
{
	// Map newMap;
	// newMap.LoadMap("lab8.txt");
	// newMap.DebugPrintMap();

	// Solver newSolver;
	// newSolver.SolveMaze(&newMap);
	RunTests();

	return 0;
}

void RunTests()
{
	TestTree::Construction();
	// TestTree::Equality();
	// TestTree::Similarity();
	// TestTree::Combine();
}