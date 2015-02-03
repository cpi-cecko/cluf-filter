#include "stdafx.h"
#include "Solver.h"

#include <vector>
#include <iostream>
#include <algorithm>

#include "Map.h"
#include "BFSPathfinder.h"
#include "PathInfo.h"



static std::string PathToString(const PathInfo &path);
static std::string CompressPath(const std::string &strPath);

void Solver::SolveMaze(Map *mazeMap)
{
	Pathfinder *bfsFinder = new BFSPathfinder();

	PathInfo path = bfsFinder->FindPath(mazeMap->GetStartTile(), mazeMap->GetExitTile());

	if ( ! path.path.empty())
	{
		std::string strPath = PathToString(path);
		std::string compressedPath = CompressPath(strPath);

		std::cout << "(" << path.start->GetSymbol() << ", " << path.end->GetSymbol() << ") ";
		std::cout << strPath << "\n\n";
		std::cout << '\t' << compressedPath << "\n\n";
	}
}

static std::string CompressPath(const std::string &path)
{
	std::string compressedPath = "";

	char currentChar = path[0];
	int charCount = 0;
	for (size_t i = 1; i < path.length(); ++i)
	{
		if (currentChar == path[i])
		{
			++charCount;
		}
		else
		{
			if (charCount > 0)
				compressedPath += std::to_string(charCount + 1);
			compressedPath += currentChar;
			currentChar = path[i];
			charCount = 0;

			if (compressedPath.size() % 8 == 0)
			{
				compressedPath += " ";
			}
		}
	}
	if (charCount > 0)
		compressedPath += std::to_string(charCount + 1);
	compressedPath += currentChar;
	charCount = 0;

	return compressedPath;
}

static std::string PathToString(const PathInfo &info)
{
	std::string path = "";
	for (auto dirIt = info.path.begin(); dirIt != info.path.end(); ++dirIt)
	{
		switch ((*dirIt))
		{
		case DIR_UP:
			path += "U";
			break;
		case DIR_DOWN:
			path += "D";
			break;
		case DIR_RIGHT:
			path += "R";
			break;
		case DIR_LEFT:
			path += "L";
			break;
		default:
			std::cerr << "Invalid direction\n";
			break;
		}
	}
	return path;
}