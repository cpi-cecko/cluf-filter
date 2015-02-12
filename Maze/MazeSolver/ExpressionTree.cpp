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
	ChildrenVector::iterator child = children.begin();
	while (child != children.end())
	{
		if ( ! child->op.Expression().empty())
		{
			std::string expression = child->op.Expression();
			size_t expressionLength = expression.length();
			size_t chunkLen = expressionLength / 2;
			while (chunkLen >= 1)
			{
				size_t chunkBeg = 0;
				size_t chunkEnd = chunkLen;
				size_t expressionCount = 1;
				while (chunkEnd + chunkLen < expressionLength)
				{
					assert(chunkEnd > chunkBeg);
					std::string first = expression.substr(chunkBeg, chunkLen);
					std::string second = expression.substr(chunkEnd, chunkLen);
					if (first == second) 
					{
						if (chunkEnd + chunkLen < expressionLength)
						{
							++expressionCount;
						}
						else 
						{
							// We've found a match and reached the end
							++expressionCount;
							if (expressionCount > 1)
							{
								child = Merge(child, chunkBeg, chunkLen, expressionCount);
								expressionCount = 1;
							}
							break;
						}
					}
					else
					{
						if (expressionCount > 1)
						{
							child = Merge(child, chunkBeg, chunkLen, expressionCount);
							expressionCount = 1;
							// Continue the procedure on the new child
							chunkEnd = 0;
							expression = child->op.Expression();
							expressionLength = expression.length();
						}
						chunkBeg = chunkEnd;
					}
					chunkEnd += chunkLen;
				}
				--chunkLen;
			}
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
	return children.end();
}

bool ExpressionTree::IsEqual(const ExpressionTree &other) const
{
	//if (&other)
	//{
	//	return this->ToString() == other.ToString();
	//}
	return false;
}

std::string ExpressionTree::ToString() const
{
	std::string result;

	//for (auto symbol : expression)
	//{
	//	// Positive symbols represent quotients, negative symbols represent
	//	// parens or dirs
	//	if (symbol > 1)
	//	{
	//		result += std::to_string(symbol);
	//	}
	//	else if (symbol < 0)
	//	{
	//		result += char(-symbol);
	//	}
	//}

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