#pragma once


#include <vector>

class Map;
enum Dir;

class Solver
{
public:
	void SolveMaze(Map *mazeMap);

private:
	void FindPathsToDoors(Map *mazeMap);

private:
	std::vector<std::vector<Dir>> pathsToDoors;
};