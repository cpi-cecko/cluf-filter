#include "stdafx.h"
#include "ExpressionTree.h"



ExpressionTree::ExpressionTree()
	: children(NULL), childrenCount(0)
{
}


void ExpressionTree::Construct(const std::vector<Dir> &dirs)
{
}

bool ExpressionTree::IsEqual(const ExpressionTree &other) const
{
	return false;
}
bool ExpressionTree::IsSimilar(const ExpressionTree &other) const
{
	return false;
}

std::string ExpressionTree::ToString()
{
	return "";
}

ExpressionTree* ExpressionTree::Combine(const ExpressionTree *one, const ExpressionTree *two)
{
	return NULL;
}


void ExpressionTree::CopyTree(const ExpressionTree &other)
{
	childrenCount = other.childrenCount;
	children = new ExpressionTree[childrenCount];
	for (size_t idx = 0; idx < childrenCount; ++idx)
	{
		children[idx] = other.children[idx];
	}
}

void ExpressionTree::DeleteTree()
{
	delete [] children;
}

ExpressionTree::~ExpressionTree()
{
	DeleteTree();
}

ExpressionTree::ExpressionTree(const ExpressionTree &other)
{
	CopyTree(other);
}

ExpressionTree& ExpressionTree::operator=(const ExpressionTree &other)
{
	if (this != &other)
	{
		CopyTree(other);
	}

	return *this;
}