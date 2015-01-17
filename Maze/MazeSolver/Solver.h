#pragma once


#include <vector>

class Map;
class Tile;
enum Dir;
struct PathInfo;

class Solver
{
public:
	void SolveMaze(Map *mazeMap);

private:
	void FindPathsToDoors(Map *mazeMap);

private:
	std::vector<PathInfo> pathsToDoors;
};

struct PathInfo
{
	std::vector<Dir> path;
	Tile *start;
	Tile *end;
};