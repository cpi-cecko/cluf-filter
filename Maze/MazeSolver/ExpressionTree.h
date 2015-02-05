#pragma once


#include <vector>
#include <string>


enum Dir;
class TestTree;

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
	// Combine two expression trees into one
	//
	static ExpressionTree* Combine(const TreePair &treeLeft, const TreePair &treeRight);

	//
	// Returns `true` if both trees' printable expressions are equal
	//
	bool IsEqual(const ExpressionTree &other) const;

	void AddChild(const ExpressionTree &newChild);

	const TreePair* GetChild(size_t childIdx) const;

	friend TestTree;
};