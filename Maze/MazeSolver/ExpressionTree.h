#pragma once


#include <vector>
#include <string>


enum Dir;
class TestTree;

class ExpressionTree
{
private:
	std::string op;
	std::vector<ExpressionTree> children;

public:
	ExpressionTree();
	ExpressionTree(const std::string &newOp);

	void Construct(const std::vector<Dir> &dirs);

	// The mostest importantest method of this class
	void Compress();

	std::string ToString();

	bool IsEqual(const ExpressionTree &other) const;
	bool IsSimilar(const ExpressionTree &other) const;

private:
	static ExpressionTree* Combine(const ExpressionTree *one, const ExpressionTree *two);
	void SetOp(const std::string &newOp);
	void AddChild(const ExpressionTree &newChild);

	friend TestTree;
};