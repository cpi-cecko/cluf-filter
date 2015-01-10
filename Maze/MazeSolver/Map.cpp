#include "stdafx.h"
#include "Map.h"

#include <fstream>
#include <iostream>


Map::Map()
	: map(NULL), keyDoorPairs(NULL), rowsCount(0), colsCount(0)
{
}

void Map::DebugPrintMap() const
{
	for (int row = 0; row < rowsCount; ++row)
	{
		for (int col = 0; col < colsCount; ++col)
		{
			std::cout << map[row][col].GetSymbol();
		}
		std::cout << '\n';
	}

	for (int idx = 0; idx < keyDoorPairsCount; ++idx)
	{
		std::cout << "(" << keyDoorPairs[idx].door << ", " << keyDoorPairs[idx].key << ")\n";
	}
}

const Tile* Map::GetStartTile() const
{
	for (int row = 0; row < rowsCount; ++row)
	{
		for (int col = 0; col < colsCount; ++col)
		{
			if (map[row][col].IsStart())
				return &map[row][col];
		}
	}

	return NULL;
}

const Tile* Map::GetExitTile() const
{
	for (int row = 0; row < rowsCount; ++row)
	{
		for (int col = 0; col < colsCount; ++col)
		{
			if (map[row][col].IsExit())
				return &map[row][col];
		}
	}

	return NULL;
}

bool Map::LoadMap(const std::string &mapFileName)
{
	std::ifstream mapFile(mapFileName);

	if ( ! mapFile.is_open())
	{
		mapFile.close();
		std::cerr << "Can't open map file\n";
		return false;
	}

	int rows = 0;
	int cols = 0;
	int pairsCount = 0;

	if ( ! ReadMapKeysSize(mapFile, rows, cols, pairsCount))
	{
		std::cerr << "Failed to get map size\n";
		return false;
	}

	Tile **newMap = AllocateTiles(rows, cols);

	if ( ! ReadMap(mapFile, newMap))
	{
		std::cerr << "Failed to load map\n";
		return false;
	}

	FreeMap(map, rowsCount);
	map = newMap;
	rowsCount = rows;
	colsCount = cols;

	KeyPair *keyPairs = AllocateKeyDoorPairs(pairsCount);

	if ( ! ReadKeys(mapFile, keyPairs))
	{
		std::cerr << "Failed to read keys\n";
		return false;
	}

	FreeKeys(keyDoorPairs);
	keyDoorPairs = keyPairs;
	keyDoorPairsCount = pairsCount;

	mapFile.close();
	return true;
}

bool Map::ReadMapKeysSize(std::ifstream &mapFile, int &rowsRead, int &colsRead, int &pairsCount)
{
	mapFile.clear();
	mapFile.seekg(0, std::ios::beg);


	int rows = 0;
	int cols = 0;
	int pairs = 0;
	int colCounter = 0; // used to validate column count
	int keyCounter = 0; // used to validate key parts count
	char ch;
	bool isReadingKeys = false;

	while (mapFile.get(ch) && ch != '\n')
			++cols;

	if (cols > 0)
	{
		++rows;

		while (mapFile.get(ch))
		{
			if (ch == '\n')
			{
				if (colCounter == 0 && ! isReadingKeys)
				{
					isReadingKeys = true;
					continue;
				}

				if (isReadingKeys)
				{
					if (keyCounter != 2)
					{
						std::cerr << "Bad keys\n";
						return false;
					}

					++pairs;
					keyCounter = 0;
				}
				else
				{
					if (colCounter != cols)
					{
						std::cerr << "Uneven number of columns in map\n";
						return false;
					}

					++rows;
					colCounter = 0;
				}
			}
			else
			{
				isReadingKeys ? ++keyCounter : ++colCounter;
			}
		}

		if (ch != '\n' && isReadingKeys)
		{
			if (keyCounter != 2)
			{
				std::cerr << "Bad keys\n";
				return false;
			}

			++pairs;
		}
	}

	rowsRead = rows;
	colsRead = cols;
	pairsCount = pairs;

	return true;
}

bool Map::ReadMap(std::ifstream &mapFile, Tile **inMap)
{
	mapFile.clear();
	mapFile.seekg(0, std::ios::beg);


	int row = 0;
	int col = 0;
	char ch;

	while (mapFile.get(ch))
	{
		if (ch != '\n')
		{
			inMap[row][col] = Tile(Position(row, col), ch);
			inMap[row][col].SetOwner(this);
			++col;
		}
		else
		{
			if (col == 0) // switch to reading keys
			{
				break;
			}
			else
			{
				++row;
				col = 0;
			}
		}
	}


	return true;
}

bool Map::ReadKeys(std::ifstream &mapFile, KeyPair *inKeyDoorPairs)
{
	mapFile.clear();
	mapFile.seekg(0, std::ios::beg);


	int currentPairIdx = 0;
	int cols = 0;
	char ch;
	bool isReadingKeys = false;
	bool isOnDoor = false;

	while (mapFile.get(ch))
	{
		if (isReadingKeys && ch != '\n')
		{
			if (isOnDoor)
			{
				inKeyDoorPairs[currentPairIdx].door = ch;
				isOnDoor = false;
			}
			else
			{
				inKeyDoorPairs[currentPairIdx].key = ch;
				isOnDoor = true;
				// only increment pair idx if we've read a whole key line
				++currentPairIdx;
			}
		}
		else
		{
			if (ch != '\n')
			{
				++cols;
			}
			else
			{
				isReadingKeys = cols == 0;
				isOnDoor = isReadingKeys;
				cols = 0;
			}
		}
	}


	return true;
}


Tile** Map::AllocateTiles(int rows, int cols)
{
	Tile **newMap = NULL;

	try
	{
		newMap = new Tile*[rows];

		for (int row = 0; row < rows; ++row)
		{
			newMap[row] = new Tile[cols];
		}
	}
	catch (std::bad_alloc&)
	{
		FreeMap(newMap, rows);
	}

	if (newMap)
	{
		SetAsOwnerFor(newMap, rows, cols);
	}

	return newMap;
}

void Map::SetAsOwnerFor(Tile **newMap, int rows, int cols)
{
	for (int row = 0; row < rows; ++row)
	{
		for (int col = 0; col < cols; ++col)
		{
			newMap[row][col].SetOwner(this);
		}
	}
}

KeyPair* Map::AllocateKeyDoorPairs(int size)
{
	KeyPair *newPairs = NULL;

	try
	{
		newPairs = new KeyPair[size];
	}
	catch (std::bad_alloc&)
	{
		FreeKeys(newPairs);
	}

	return newPairs;
}

void Map::FreeMap(Tile **&toFree, int rowsCount)
{
	if ( ! toFree)
	{
		return;
	}

	for (int row = 0; row < rowsCount; ++row)
	{
		delete [] toFree[row];
	}
	delete [] toFree;

	map = NULL;
}

void Map::FreeKeys(KeyPair *toFree)
{
	delete [] toFree;
	toFree = NULL;
}

Map::~Map()
{
	FreeMap(map, rowsCount);
	FreeKeys(keyDoorPairs);
}