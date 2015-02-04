#include "stdafx.h"
#include "ExpressionTree.h"
#include "Tile.h"

#include <iostream>
#include <cctype>


ExpressionTree::ExpressionTree()
	: children(), op("")
{
}

ExpressionTree::ExpressionTree(const std::string &newOp)
	: op(newOp)
{
}


std::string DirToString(Dir dir);

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
			ExpressionTree child;
			if (dirCount > 1)
			{
				child.SetOp(std::to_string(dirCount));
				child.AddChild(ExpressionTree(DirToString(dirs[idx])));
			}
			else
			{
				child.SetOp(DirToString(dirs[idx]));
			}
			children.push_back(child);
			dirCount = 1;
		}
	}
}

std::string DirToString(Dir dir)
{
	switch (dir)
	{
	case DIR_UP:
		return "U";
	case DIR_DOWN:
		return "D";
	case DIR_LEFT:
		return "L";
	case DIR_RIGHT:
		return "R";
	default:
		std::cerr << "Invalid dir " << dir;
		return "";
	}
}

bool ExpressionTree::IsEqual(const ExpressionTree &other) const
{
	if (&other)
		return this->ToString() == other.ToString();
	return false;
}
bool ExpressionTree::IsSimilar(const ExpressionTree &other) const
{
	return false;
}

bool is_number(const std::string &str)
{
	std::string::const_iterator it = str.begin();
	while (it != str.end() && std::isdigit(*it)) ++it;
	return !str.empty() && it == str.end();
}

std::string ExpressionTree::ToString() const
{
	std::string result("");

	for (auto child : children)
	{
		result += child.op;
		result += child.ToString();
	}

	return result;
}

ExpressionTree* ExpressionTree::Combine(const std::vector<ExpressionTree> &trees)
{
	ExpressionTree *newTree = new ExpressionTree(std::to_string(trees.size()));
	newTree->AddChild(trees[0]);
	return newTree;
}


void ExpressionTree::SetOp(const std::string &newOp)
{
	op = newOp;
}

void ExpressionTree::AddChild(const ExpressionTree &newChild)
{
	children.push_back(newChild);
}