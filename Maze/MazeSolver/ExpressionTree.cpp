#include "stdafx.h"
#include "ExpressionTree.h"
#include "Tile.h"

#include <iostream>
#include <cctype>
#include <assert.h>


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

void ExpressionTree::Compress()
{
	// Get first child
	// Compare it to the second
	// If match, merge and do the same with the next pair
	// Else get first and second children
	// Compare them to the third and fourth
	// If match, merge and do the same with the next pair
	// Continue until middle
	size_t middle = children.size() / 2;
	size_t currLast = 1;
	size_t idxIncr = 1;
	for (size_t idx = 0; idx < currLast; idx += idxIncr)
	{
		ExpressionTree *combinedLeft = Combine(std::vector<TreePair>(children.begin() + idx, 
																	 children.begin() + currLast - 1));
		ExpressionTree *combinedRight = Combine(std::vector<TreePair>(children.begin() + currLast,
																	  children.begin() + idx + currLast));
		if (combinedLeft->IsEqual(*combinedRight))
		{
			Merge(*combinedLeft, *combinedRight);
			if (currLast < middle)
				currLast++;
		}
		else
		{
			currLast++;
			idxIncr++;
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

ExpressionTree* ExpressionTree::Combine(const std::vector<TreePair> &subTrees)
{
	ExpressionTree *combinedTree = new ExpressionTree();

	for (auto sub : subTrees)
	{
		combinedTree->children.push_back(sub);
	}

	return combinedTree;
}

void ExpressionTree::Merge(const ExpressionTree &left, const ExpressionTree &right)
{
}


const ExpressionTree::TreePair* ExpressionTree::GetChild(size_t childIdx) const
{
	return &children[childIdx];
}