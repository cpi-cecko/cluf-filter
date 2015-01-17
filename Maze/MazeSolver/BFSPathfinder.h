#pragma once


#include "Pathfinder.h"

#include <vector>
#include <queue>


class BFSPathfinder : public Pathfinder
{
private:
	virtual std::vector<Dir> DoFindPath(Tile *start, Tile *end);

	void AddIfPassable(Tile *currentTile, Tile *parent, Tile *end);

private:
	std::queue<Tile*> walkedTiles;
	std::vector<Dir> path;
	std::vector<Tile*> bestNeighbourForNode;
};