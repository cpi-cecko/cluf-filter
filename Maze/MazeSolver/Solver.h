#pragma once


class Map;
class Tile;
enum Dir;

class Solver
{
public:
	//
	// Solves the given maze using BFSPathfinder and
	// compresses the output path after that.
	//
	void SolveMaze(Map *mazeMap);
};
