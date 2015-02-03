#pragma once


#include <vector>
#include <string>


enum Dir;
class TestTree;

class ExpressionTree
{
private:
	size_t childrenCount;
	ExpressionTree *children;

public:
	ExpressionTree();

	void Construct(const std::vector<Dir> &dirs);

	// The mostest importantest method of this class
	void Compress();

	std::string ToString();

	bool IsEqual(const ExpressionTree &other) const;
	bool IsSimilar(const ExpressionTree &other) const;

private:
	static ExpressionTree* Combine(const ExpressionTree *one, const ExpressionTree *two);


public:
	~ExpressionTree();
	ExpressionTree(const ExpressionTree &other);
	ExpressionTree& operator=(const ExpressionTree &other);

private:
	void CopyTree(const ExpressionTree &other);
	void DeleteTree();

	friend TestTree;
};