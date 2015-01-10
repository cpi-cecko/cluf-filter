#pragma once


#include "Tile.h"

#include <string>


struct KeyPair;

class Map
{
private:
	Tile **map;
	KeyPair *keyDoorPairs;

	int rowsCount;
	int colsCount;
	int keyDoorPairsCount;

public:
	Map(); 
	~Map();

	bool LoadMap(const std::string &mapFileName);
	void DebugPrintMap() const;

private:
	Tile** AllocateTiles(int rows, int cols);
	KeyPair* AllocateKeyDoorPairs(int size);
	void FreeMap(Tile **&toFree, int rows);
	void FreeKeys(KeyPair *toFree);

	bool ReadMapKeysSize(std::ifstream &mapFile, int &rows, int &cols, int &pairsCount);
	bool ReadMap(std::ifstream &mapFile, Tile **inMap);
	bool ReadKeys(std::ifstream &mapFile, KeyPair *inKeyDoorPairs);

	void SetAsOwnerFor(Tile **ownerMap, int rows, int cols);

private:
	Map(const Map &other);
	Map& operator=(const Map &other);
};


struct KeyPair
{
	char key;
	char door;
};