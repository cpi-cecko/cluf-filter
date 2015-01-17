#pragma once


class Tile;
enum Dir;

struct PathInfo
{
	std::vector<Dir> path;
	Tile *start;
	Tile *end;

	PathInfo()
		: path(), start(NULL), end(NULL)
	{
	}

	PathInfo(const std::vector<Dir> &newPath, Tile *newStart, Tile *newEnd)
		: path(newPath), start(newStart), end(newEnd)
	{
	}
};