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

	void Construct(const std::vector<Dir> &dirs);

	void Compress();

	std::string ToString() const;

private:
	ChildrenVector::iterator Merge(ChildrenVector::iterator which, size_t chunkBeg, size_t chunkLen, size_t chunkCount);

	bool IsEqual(const ExpressionTree &other) const;
	void SetOp(const Node &newOp);

	friend TestTree;
};

/*
//
// Should be:
//    ExpTree = ExpTree Char [(Int, ExpTree)]
//
class ExpressionTree
{
private:
	char dir;

	typedef std::pair<int, ExpressionTree> TreePair;
	std::vector<TreePair> children;

public:
	ExpressionTree();
	ExpressionTree(char newDir);

	//
	// Given a vector of dirs, constructs a tree such that each leaf shows the direction followed by 
	//	its repetition count.
	//
	// UUDDRRRRL =>   /-2-U
	//				/-|-2-D
	//				  |-4-R
	//				  \-1-L
	//
	void Construct(const std::vector<Dir> &dirs);

	// The mostest importantest method of this class
	void Compress();

	//
	// Recurses the tree and creates a printable expression from it
	//
	std::string ToString() const;

private:
	//
	// Puts all subtrees under a common root
	//
	static ExpressionTree* Combine(const std::vector<TreePair> &subTrees);

	//
	// Merges two subtrees into one in this tree
	//
	void Merge(const ExpressionTree &left, const ExpressionTree &right);

	//
	// Returns `true` if both trees' printable expressions are equal
	//
	bool IsEqual(const ExpressionTree &other) const;

	void AddChild(const ExpressionTree &newChild);

	const TreePair* GetChild(size_t childIdx) const;

	friend TestTree;
};
*/