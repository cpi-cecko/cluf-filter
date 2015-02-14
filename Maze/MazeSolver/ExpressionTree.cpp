#include "stdafx.h"
#include "ExpressionTree.h"
#include "Tile.h"

#include <iostream>
#include <cctype>
#include <assert.h>


ExpressionTree::ExpressionTree()
	: op(), children()
{
}

ExpressionTree::ExpressionTree(const std::string &expressionOp)
	: op(expressionOp), children()
{
}

ExpressionTree::ExpressionTree(int countOp)
	: op(countOp), children()
{
}

void ExpressionTree::Construct(const std::vector<Dir> &dirs)
{
	children.clear();

	std::string expression;
	for (size_t idx = 0; idx < dirs.size(); ++idx)
	{
		expression.push_back(dirs[idx]);
	}

	ExpressionTree child;
	child.SetOp(Node(expression));
	children.push_back(child);
}

void ExpressionTree::Compress()
{
	CompressOne();
	CompressTwo();
}

void ExpressionTree::CompressOne()
{
	auto child = children.begin();
	while (child != children.end())
	{
		std::string expression = child->op.Expression();
		size_t expressionLen = expression.length();
		size_t expressionCount = 1;
		size_t chunkIdx = 0;
		size_t chunkBeg = 0;
		size_t chunkSize = 1;
		while (chunkIdx < expressionLen)
		{
			chunkBeg = chunkIdx;
			while (chunkIdx < expressionLen && 
				   expression[chunkIdx] == expression[chunkIdx + 1])
			{
				expressionCount++;
				chunkIdx++;
			}
			if (expressionCount > 1)
			{
				child = Merge(child, chunkBeg, 1, expressionCount);
				chunkIdx = 0;
				expressionCount = 1;
				expression = child->op.Expression();
				expressionLen = expression.length();
			}
			++chunkIdx;
		}

		if (child != children.end())
			++child;
	}
}

void ExpressionTree::CompressTwo()
{
	auto child = children.begin();
	while (child != children.end())
	{
		std::string expression = child->op.Expression();
		size_t expressionLen = expression.length();
		size_t chunkLen = expressionLen / 2;
		size_t chunkBeg = 0;
		size_t chunkEnd = chunkBeg + chunkLen;
		size_t chunk2Beg = chunkEnd;
		size_t chunk2End = chunkEnd + chunkLen;
		size_t expressionCount = 1;
		while (chunkLen >= 1)
		{
			while (chunkEnd <= expressionLen && chunk2End <= expressionLen)
			{
				std::string first = expression.substr(chunkBeg, chunkLen);
				std::string second = expression.substr(chunk2Beg, chunkLen);
				chunk2Beg += chunkLen;
				chunk2End += chunkLen;
				if (first == second)
				{
					++expressionCount;
					if (chunk2End >= expressionLen)
					{
						if (child->op.Expression() != "")
						{
							child = Merge(child, chunkBeg, chunkLen, expressionCount);
							child->Compress();
						}
						chunkLen = 0;
						break;
					}
				}
				else
				{
					if (expressionCount > 1)
					{
						if (child->op.Expression() != "")
						{
							child = Merge(child, chunkBeg, chunkLen, expressionCount);
							child->Compress();
						}
					}
					chunkBeg += chunkLen;
					chunkEnd += chunkLen;
				}
			}
			chunkLen -= chunkLen > 0 ? 1 : 0;
			chunkBeg = 0;
			chunkEnd = chunkBeg + chunkLen;
			chunk2Beg = chunkEnd;
			chunk2End = chunkEnd + chunkLen;
		}

		if (child != children.end())
			++child;
	}
}

ExpressionTree::ChildrenVector::iterator ExpressionTree::Merge(ChildrenVector::iterator which,
															   size_t chunkBeg, size_t chunkLen,
															   size_t chunkCount)
{
	// Split `which`'s expression in three at `chunkBeg`
	//	first = exp[:chunkBeg]
	//	second = exp[chunkBeg:chunkBeg + chunkLen]
	//	third = exp[chunkBeg + chunkCount * chunkLen:]
	// Put third before which
	// Put second before third but with `chunkCount` as count
	// Put first before second
	// return children.erase(which);
	assert(which->op.Expression() != "");

	auto splitExpression = SplitAt(which, chunkBeg, chunkLen, chunkCount);
	size_t toIncrement = 1;
	size_t toDecrement = 0;
	if (splitExpression[2] != "")
	{
		which = InsertBefore(which, splitExpression[2]);
		++toIncrement;
		++toDecrement;
	}
	which = InsertBeforeWithCount(which, splitExpression[1], chunkCount);
	if (splitExpression[0] != "")
	{
		which = InsertBefore(which, splitExpression[0]);
		++toIncrement;
	}

	// Make `which` point back to where it was at the beginning.
	which += toIncrement;
	which = Remove(which);
	return which - toDecrement;
}

std::vector<std::string> ExpressionTree::SplitAt(ChildrenVector::iterator which,
												 size_t chunkBeg, size_t chunkLen, size_t chunkCount) const
{
	std::string expression = which->op.Expression();
	std::vector<std::string> splitThree;
	splitThree.push_back(expression.substr(0, chunkBeg));
	splitThree.push_back(expression.substr(chunkBeg, chunkLen));
	splitThree.push_back(expression.substr(chunkBeg + chunkLen * chunkCount));

	return splitThree;
}

ExpressionTree::ChildrenVector::iterator ExpressionTree::InsertBefore(ChildrenVector::iterator which,
																	  const std::string &expression)
{
	return children.insert(which, ExpressionTree(expression));
}

ExpressionTree::ChildrenVector::iterator ExpressionTree::InsertBeforeWithCount(ChildrenVector::iterator which,
																			   const std::string &expression,
																			   int count)
{
	ExpressionTree countTree(count);
	countTree.Insert(ExpressionTree(expression));
	return children.insert(which, countTree);
}

void ExpressionTree::Insert(const ExpressionTree &tree)
{
	children.push_back(tree);
}

ExpressionTree::ChildrenVector::iterator ExpressionTree::Remove(ChildrenVector::iterator which)
{
	ChildrenVector::iterator beforeWhich = which - 1;
	children.erase(which);
	return beforeWhich;
}

std::string ExpressionTree::ToString() const
{
	std::string result;

	for (auto child : children)
	{
		if (child.op.Count() > 0)
		{
			int count = child.op.Count();
			result += std::to_string(child.op.Count());
			if (child.children.size() > 1 || child.children[0].op.Expression().length() != 1)
				result += "(";
			result += child.ToString();
			if (child.children.size() > 1 || child.children[0].op.Expression().length() != 1)
				result += ")";
		}
		else
		{
			result += child.op.Expression();
		}
	}

	return result;
}

void ExpressionTree::SetOp(const Node &newOp)
{
	op = newOp;
}

//////////
// Node //
//////////
Node::Node()
	: count(0), expression("")
{
}

Node::Node(int newCount)
	: count(newCount), expression("")
{
}

Node::Node(const std::string &newExpression)
	: expression(newExpression), count(0)
{
}

int Node::Count() const
{
	return count;
}

const std::string& Node::Expression() const
{
	return expression;
}