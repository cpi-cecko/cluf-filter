#pragma once


class Tile;
enum Symbol;

struct PathInfo
{
	std::vector<Symbol> path;
	Tile *start;
	Tile *end;

	PathInfo()
		: path(), start(NULL), end(NULL)
	{
	}

	PathInfo(const std::vector<Symbol> &newPath, Tile *newStart, Tile *newEnd)
		: path(newPath), start(newStart), end(newEnd)
	{
	}
};