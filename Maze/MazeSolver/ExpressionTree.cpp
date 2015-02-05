#include "stdafx.h"
#include "ExpressionTree.h"
#include "Tile.h"

#include <iostream>
#include <cctype>


ExpressionTree::ExpressionTree()
	: children(), dir(char(DIR_INVALID))
{
}
ExpressionTree::ExpressionTree(char newDir)
	: children(), dir(newDir)
{
}

void ExpressionTree::Construct(const std::vector<Dir> &dirs)
{
	children.clear();

	size_t dirCount = 1;
	for (size_t idx = 0; idx < dirs.size(); ++idx)
	{
		if (idx < dirs.size() - 1 && dirs[idx] == dirs[idx+1])
		{
			++dirCount;
		}
		else
		{
			children.push_back(std::make_pair(dirCount, char(dirs[idx])));
			dirCount = 1;
		}
	}
}

bool ExpressionTree::IsEqual(const ExpressionTree &other) const
{
	if (&other)
	{
		return this->ToString() == other.ToString();
	}
	return false;
}
bool ExpressionTree::IsSimilar(const ExpressionTree &other) const
{
	return false;
}

std::string ExpressionTree::ToString() const
{
	std::string result;
	if (dir != char(DIR_INVALID))
	{
		result += dir;
	}

	for (auto child : children)
	{
		if (child.first > 1)
		{
			result += std::to_string(child.first);
		}
		result += child.second.ToString();
	}

	return result;
}

ExpressionTree* ExpressionTree::Combine(const std::vector<ExpressionTree> &trees)
{
	return NULL;
}