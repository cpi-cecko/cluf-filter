#pragma once


#include "Pathfinder.h"

#include <vector>
#include <queue>


class Tile;

class BFSPathfinder : public Pathfinder
{
private:
	virtual PathInfo DoFindPath(Tile *start, Tile *end);

	std::vector<Tile*> CalculateBestNeighbours(Tile *start, Tile *end);
	std::vector<Tile*> GetDoorsFromPath(Tile *start, Tile *end, const std::vector<Tile*> &bestNeighbours);
	PathInfo GetPathFromBestNeighbours(Tile *start, Tile *end, 
									   const std::vector<Tile*> &bestNeighbours);
};