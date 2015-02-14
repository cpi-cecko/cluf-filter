#pragma once


#include "Pathfinder.h"

#include <vector>
#include <list>


class Tile;

class BFSPathfinder : public Pathfinder
{
private:
	//
	// Finds the path through a maze with locked doors.
	// The algorithm works as follows, we first find the path to the exit, 
	// without taking into an account that the doors are locked. After that,
	// we take only the doors from the path and expand the given array by finding
	// the required keys for the doors and additional doors we have to go through.
	// In the end, we expand the vector by providing the paths to every element.
	// 
	virtual PathInfo DoFindPath(Tile *start, Tile *end);

	//
	// Finds the best neighbours for each node. From these we could easily calculate
	// the best path from the End to the Start.
	//
	std::vector<Tile*> CalculateBestNeighbours(Tile *start, Tile *end);
	//
	// Extracts doors from a given vector of best neighbours.
	//
	std::list<Tile*> GetDoorsFromPath(Tile *start, Tile *end, const std::vector<Tile*> &bestNeighbours);
	//
	// Extracts a human-readable path from a vector of best neighbours.
	//
	PathInfo GetPathFromBestNeighbours(Tile *start, Tile *end, 
									   const std::vector<Tile*> &bestNeighbours);
};