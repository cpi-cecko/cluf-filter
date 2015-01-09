#pragma once


#include "Tile.h"

#include <string>


class Map
{
private:
	Tile **map;

	int rowsCount;
	int colsCount;

public:
	Map(); 
	~Map();

	bool LoadMap(const std::string &mapFileName);
	void DebugPrintMap() const;

private:
	Tile** AllocateTiles(int rows, int cols);
	void FreeMap(Tile **&toFree, int rows);

	bool ReadMapSize(std::ifstream &mapFile, int &rows, int &cols);
	bool ReadMap(std::ifstream &mapFile, Tile **inMap);

	void SetAsOwnerFor(Tile **ownerMap, int rows, int cols);

private:
	Map(const Map &other);
	Map& operator=(const Map &other);
};