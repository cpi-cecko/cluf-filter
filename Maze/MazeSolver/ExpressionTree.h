#pragma once


#include <vector>
#include <string>


enum Dir;
class TestTree;

//
// (Maybe Int, Maybe String)
//
class Node
{
private:
	// if both are invalid, the node is Nothing
	int count; // count <= 0 is invalid
	std::string expression; // empty expression is invalid

public:
	// Creates the Nothing node, e.g. a node with both members invalid
	explicit Node();
	Node(int newCount);
	Node(const std::string &newExpression);

	int Count() const;
	const std::string& Expression() const;
};

//
// An expression represented as a tree, where each node is either a count,
// a string of directions or Nothing.
//
class ExpressionTree
{
private:
	Node op;
	typedef std::vector<ExpressionTree> ChildrenVector;
	ChildrenVector children;

public:
	ExpressionTree();
	ExpressionTree(const std::string &expressionOp);
	ExpressionTree(int countOp);

	//
	// Constructs the expression tree by converting `dirs` to string and setting them as the only child.
	//
	void Construct(const std::vector<Dir> &dirs);

	//
	// Compresses the tree, going through two phases.
	// In phase one, we merge every single-character occurences in separate subtrees.
	// In phase two, we try to find multi-character sequences.
	//
	void Compress();

	std::string ToString() const;

private:
	//
	// Goes through the tree and compresses consequetive equal characters.
	//
	void CompressOne();
	//
	// Goes through the tree and tries to compress strings of characters.
	//
	void CompressTwo();

	//
	// Splits the subtree's expression in three
	// The first resembles the string before the compressed expression,
	// the second resembles the compressed expression,
	// and the third resembles the string after the compressed expression.
	// These three are inserted as new children of the tree.
	//
	ChildrenVector::iterator Merge(ChildrenVector::iterator which,
								   size_t chunkBeg, size_t chunkLen, size_t chunkCount);

	//
	// Splits a subtree's expression in three.
	//
	std::vector<std::string> SplitAt(ChildrenVector::iterator which,
									 size_t chunkBeg, size_t chunkLen, size_t chunkCount) const;
	//
	// Inserts before `which`
	//
	ChildrenVector::iterator InsertBefore(ChildrenVector::iterator which, const std::string &expression);
	//
	// Inserts before `which` but with count provided
	//
	ChildrenVector::iterator InsertBeforeWithCount(ChildrenVector::iterator which,
												   const std::string &expression, int count);
	//
	// Inserts a new child
	//
	void Insert(const ExpressionTree &what);

	//
	// Removes a child
	//
	ChildrenVector::iterator Remove(ChildrenVector::iterator which);

	void SetOp(const Node &newOp);
};