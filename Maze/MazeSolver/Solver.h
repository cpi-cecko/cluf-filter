#pragma once


#include <vector>
#include "PathInfo.h"

class Map;
class Tile;
enum Dir;

class Solver
{
public:
	void SolveMaze(Map *mazeMap);

private:
	void FindPathsToDoors(Map *mazeMap);

private:
	std::vector<PathInfo> pathsToDoors;
};
