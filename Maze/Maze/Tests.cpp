#include "Tests.h"

#include "../MazeSolver/ExpressionTree.h"
#include "../MazeSolver/Tile.h"

#include <vector>
#include <assert.h>


#define ARR_SIZE(arr, type) sizeof(arr) / sizeof(type)

void TestTree::Construction()
{
	ExpressionTree newTree;
	Symbol dirs[] = { DIR_UP, DIR_UP, DIR_DOWN, DIR_DOWN };
	std::vector<Symbol> dirVector(&dirs[0], &dirs[ARR_SIZE(dirs, Symbol)]);
	newTree.Construct(dirVector);
	std::string str = newTree.ToString();
	assert(newTree.ToString() == "2U2D");

	dirVector.clear();
	newTree.Construct(dirVector);
	assert(newTree.ToString() == "");

	Symbol dirs2[] = { DIR_UP, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_UP, DIR_DOWN,
					DIR_LEFT, DIR_LEFT, DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_RIGHT, DIR_RIGHT, DIR_LEFT };
	dirVector.insert(dirVector.end(), &dirs2[0], &dirs2[ARR_SIZE(dirs2, Symbol)]);
	newTree.Construct(dirVector);
	assert(newTree.ToString() == "U3RUDUD3LRU2RL");

	dirVector.clear();
	Symbol dirs3[] = { DIR_RIGHT, DIR_RIGHT, DIR_DOWN, DIR_DOWN, DIR_LEFT, DIR_DOWN, DIR_DOWN, DIR_DOWN,
					DIR_RIGHT, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP, DIR_UP, DIR_RIGHT, DIR_UP, DIR_RIGHT,
					DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_LEFT, DIR_LEFT, DIR_LEFT,
					DIR_LEFT, DIR_DOWN, DIR_DOWN, DIR_DOWN, DIR_DOWN, DIR_RIGHT, DIR_RIGHT, DIR_DOWN,
					DIR_DOWN, DIR_DOWN, DIR_DOWN, DIR_RIGHT, DIR_RIGHT, DIR_DOWN, DIR_DOWN, DIR_DOWN,
					DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT };
	dirVector.insert(dirVector.end(), &dirs3[0], &dirs3[ARR_SIZE(dirs3, Symbol)]);
	newTree.Construct(dirVector);
	assert(newTree.ToString() == "2R2DL3DR2UL2URU6R4L4D2R4D2R3D5R");
}

void TestTree::Equality()
{
	ExpressionTree first;
	ExpressionTree second;
	Symbol dirs[] = { DIR_DOWN, DIR_RIGHT };
	std::vector<Symbol> dirVector(&dirs[0], &dirs[ARR_SIZE(dirs, Symbol)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	assert(first.IsEqual(second));

	Symbol dirs2[] = { DIR_DOWN, DIR_DOWN, DIR_RIGHT };
	dirVector.clear();
	dirVector.insert(dirVector.end(), &dirs2[0], &dirs2[ARR_SIZE(dirs2, Symbol)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	assert(first.IsEqual(second));

	Symbol dirs3[] = { DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
					DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP,
					DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
					DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP };
	dirVector.clear();
	dirVector.insert(dirVector.end(), &dirs3[0], &dirs3[ARR_SIZE(dirs3, Symbol)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	assert(first.IsEqual(second));
	//std::vector<std::pair<int, ExpressionTree>> trees;
	//trees.push_back(std::make_pair(1, first));
	//trees.push_back(std::make_pair(1, second));
	//ExpressionTree *third = ExpressionTree::Combine(trees);
	//ExpressionTree *fourth = ExpressionTree::Combine(trees);
	//assert(third->IsEqual(*fourth));

	// delete third;
	// delete fourth;
}

void TestTree::Combine()
{
	ExpressionTree first;
	ExpressionTree second;
	Symbol dirs[] = { DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
				   DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP,
				   DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
				   DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP };
	std::vector<Symbol> dirVector(&dirs[0], &dirs[ARR_SIZE(dirs, Symbol)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	//std::vector<ExpressionTree> trees;
	//trees.push_back(first);
	//trees.push_back(second);
	//ExpressionTree *third = ExpressionTree::Combine(trees);
	//assert(third->ToString() == "2(2(3UL)U)");

	//delete third;
}