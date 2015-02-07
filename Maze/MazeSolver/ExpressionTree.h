#pragma once


#include <vector>
#include <string>


enum Symbol;
class TestTree;

//
// An expression represented as a vector of its operands.
//
class ExpressionTree
{
private:
	std::vector<int> expression; // int is disguised Symbol

public:
	ExpressionTree();

	void Construct(const std::vector<Symbol> &dirs);

	void Compress();

	std::string ToString() const;

private:
	//static ExpressionTree* Combine(const std::vector<TreePair> &subTrees);

	void Merge(const ExpressionTree &left, const ExpressionTree &right);

	bool IsEqual(const ExpressionTree &other) const;

	void AddChild(const ExpressionTree &newChild);

	// const TreePair* GetChild(size_t childIdx) const;

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
	void Construct(const std::vector<Symbol> &dirs);

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