#include "stdafx.h"
#include "ExpressionTree.h"
#include "Tile.h"

#include <iostream>
#include <cctype>
#include <assert.h>


ExpressionTree::ExpressionTree()
	: expression()
{
}

void ExpressionTree::Construct(const std::vector<Symbol> &dirs)
{
	expression.clear();

	size_t dirCount = 1;
	for (size_t idx = 0; idx < dirs.size(); ++idx)
	{
		if (idx < dirs.size() - 1 && dirs[idx] == dirs[idx+1])
		{
			++dirCount;
		}
		else
		{
			expression.push_back(dirCount);
			expression.push_back(dirs[idx]);
			dirCount = 1;
		}
	}
}

void ExpressionTree::Compress()
{
	size_t count = 1;
	size_t beg = 0;
	while (count < expression.size() / 2 ||
		   beg > expression.size() - count)
	{
		std::vector<int> &firstCount = GetNSymbolsFrom(beg, count);
		std::vector<int> &secondCount = GetNSymbolsFrom(count + 1, count);
		if (IsEqual(firstCount, secondCount))
		{
			MergeIn(expression, firstCount, secondCount);
			count = 1;
			++beg;
		}
		else
		{
			++count;
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

	for (auto symbol : expression)
	{
		// Positive symbols represent quotients, negative symbols represent
		// parens or dirs
		if (symbol > 1)
		{
			result += std::to_string(symbol);
		}
		else if (symbol < 0)
		{
			result += char(-symbol);
		}
	}

	return result;
}

//ExpressionTree* ExpressionTree::Combine(const std::vector<TreePair> &subTrees)
//{
//	ExpressionTree *combinedTree = new ExpressionTree();

//	for (auto sub : subTrees)
//	{
//		combinedTree->children.push_back(sub);
//	}

//	return combinedTree;
//}

void ExpressionTree::Merge(const ExpressionTree &left, const ExpressionTree &right)
{
}


//const ExpressionTree::TreePair* ExpressionTree::GetChild(size_t childIdx) const
//{
//	return &children[childIdx];
//}