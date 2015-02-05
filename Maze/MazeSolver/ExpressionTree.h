#pragma once


#include <vector>
#include <string>


enum Dir;
class TestTree;

//
// Should be:
//    ExpTree = ExpTree [(Int, (ExpTree Char))]
//
class ExpressionTree
{
private:
	char dir;
	std::vector<std::pair<int, ExpressionTree>> children;

public:
	ExpressionTree();
	ExpressionTree(char newDir);

	//
	// Given a vector of dirs, constructs a tree such that each leaf either shows the repetition count of
	// the direction followed by the direction or shows only the direction.
	//
	// UUDDRRRRL => _/___
	//	           / / / \
	//            2 2 4   L
	//            | | |
	//		      U D R
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
	static ExpressionTree* Combine(const std::vector<ExpressionTree> &trees);

	//
	// Returns `true` if both trees' printable expressions are equal
	//
	bool IsEqual(const ExpressionTree &other) const;
	//
	// Returns `true` if there's only a difference between the count with which the second expression appears
	//
	// 2(UR) ~= 5(UR)
	//
	bool IsSimilar(const ExpressionTree &other) const;

	void AddChild(const ExpressionTree &newChild);

	friend TestTree;
};