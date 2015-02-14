#include "stdafx.h"
#include "Solver.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include "Map.h"
#include "BFSPathfinder.h"
#include "PathInfo.h"
#include "ExpressionTree.h"


void Solver::SolveMaze(Map *mazeMap)
{
	Pathfinder *bfsFinder = new BFSPathfinder();

	PathInfo path = bfsFinder->FindPath(mazeMap->GetStartTile(), mazeMap->GetExitTile());

	if ( ! path.path.empty())
	{
		ExpressionTree solverTree;
		solverTree.Construct(path.path);
		std::cout << "Before: \n  ";
		std::cout << solverTree.ToString() << '\n';
		solverTree.Compress();
		std::cout << "After: \n  ";
		std::cout << solverTree.ToString() << '\n';
	}
}