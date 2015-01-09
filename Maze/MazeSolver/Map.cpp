#include "stdafx.h"
#include "Map.h"

#include <fstream>
#include <iostream>


Map::Map()
	: map(NULL), rowsCount(0), colsCount(0)
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

	if ( ! ReadMapSize(mapFile, rows, cols))
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

	mapFile.close();
	return true;
}

bool Map::ReadMapSize(std::ifstream &mapFile, int &rowsRead, int &colsRead)
{
	mapFile.clear();
	mapFile.seekg(0, std::ios::beg);


	int rows = 0;
	int cols = 0;
	int counter = 0;
	char ch;

	while (mapFile.get(ch) && ch != '\n')
			++cols;

	if (cols > 0)
	{
		++rows;

		while (mapFile.get(ch))
		{
			if (ch == '\n')
			{
				if (counter != cols)
				{
					std::cerr << "Uneven number of columns in map\n";
					return false;
				}

				++rows;
				counter = 0;
			}
			else
			{
				++counter;
			}
		}
	}

	rowsRead = rows;
	colsRead = cols;

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
			++row;
			col = 0;
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
	catch (std::bad_alloc)
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

Map::~Map()
{
	FreeMap(map, rowsCount);
}