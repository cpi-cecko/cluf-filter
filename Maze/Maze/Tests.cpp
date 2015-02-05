#include "Tests.h"

#include "../MazeSolver/ExpressionTree.h"
#include "../MazeSolver/Tile.h"

#include <vector>
#include <assert.h>


#define ARR_SIZE(arr, type) sizeof(arr) / sizeof(type)

void TestTree::Construction()
{
	ExpressionTree newTree;
	Dir dirs[] = { DIR_UP, DIR_UP, DIR_DOWN, DIR_DOWN };
	std::vector<Dir> dirVector(&dirs[0], &dirs[ARR_SIZE(dirs, Dir)]);
	newTree.Construct(dirVector);
	std::string str = newTree.ToString();
	assert(newTree.ToString() == "2U2D");

	dirVector.clear();
	newTree.Construct(dirVector);
	assert(newTree.ToString() == "");

	Dir dirs2[] = { DIR_UP, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_UP, DIR_DOWN,
					DIR_LEFT, DIR_LEFT, DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_RIGHT, DIR_RIGHT, DIR_LEFT };
	dirVector.insert(dirVector.end(), &dirs2[0], &dirs2[ARR_SIZE(dirs2, Dir)]);
	newTree.Construct(dirVector);
	assert(newTree.ToString() == "U3RUDUD3LRU2RL");

	dirVector.clear();
	Dir dirs3[] = { DIR_RIGHT, DIR_RIGHT, DIR_DOWN, DIR_DOWN, DIR_LEFT, DIR_DOWN, DIR_DOWN, DIR_DOWN,
					DIR_RIGHT, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP, DIR_UP, DIR_RIGHT, DIR_UP, DIR_RIGHT,
					DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_LEFT, DIR_LEFT, DIR_LEFT,
					DIR_LEFT, DIR_DOWN, DIR_DOWN, DIR_DOWN, DIR_DOWN, DIR_RIGHT, DIR_RIGHT, DIR_DOWN,
					DIR_DOWN, DIR_DOWN, DIR_DOWN, DIR_RIGHT, DIR_RIGHT, DIR_DOWN, DIR_DOWN, DIR_DOWN,
					DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT, DIR_RIGHT };
	dirVector.insert(dirVector.end(), &dirs3[0], &dirs3[ARR_SIZE(dirs3, Dir)]);
	newTree.Construct(dirVector);
	assert(newTree.ToString() == "2R2DL3DR2UL2URU6R4L4D2R4D2R3D5R");
}

void TestTree::Equality()
{
	ExpressionTree first;
	ExpressionTree second;
	Dir dirs[] = { DIR_DOWN, DIR_RIGHT };
	std::vector<Dir> dirVector(&dirs[0], &dirs[ARR_SIZE(dirs, Dir)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	assert(first.IsEqual(second));

	Dir dirs2[] = { DIR_DOWN, DIR_DOWN, DIR_RIGHT };
	dirVector.clear();
	dirVector.insert(dirVector.end(), &dirs2[0], &dirs2[ARR_SIZE(dirs2, Dir)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	assert(first.IsEqual(second));

	Dir dirs3[] = { DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
					DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP,
					DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
					DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP };
	dirVector.clear();
	dirVector.insert(dirVector.end(), &dirs3[0], &dirs3[ARR_SIZE(dirs3, Dir)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	assert(first.IsEqual(second));
	ExpressionTree *third = ExpressionTree::Combine(*first.GetChild(0), *second.GetChild(0));
	ExpressionTree *fourth = ExpressionTree::Combine(*first.GetChild(0), *second.GetChild(0));
	assert(third->IsEqual(*fourth));

	delete third;
	delete fourth;
}

void TestTree::Combine()
{
	ExpressionTree first;
	ExpressionTree second;
	Dir dirs[] = { DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
				   DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP,
				   DIR_UP, DIR_UP, DIR_UP, DIR_LEFT,
				   DIR_UP, DIR_UP, DIR_UP, DIR_LEFT, DIR_UP };
	std::vector<Dir> dirVector(&dirs[0], &dirs[ARR_SIZE(dirs, Dir)]);
	first.Construct(dirVector);
	second.Construct(dirVector);
	ExpressionTree *third = ExpressionTree::Combine(*first.GetChild(0), *second.GetChild(0));
	assert(third->ToString() == "2(2(3UL)U)");

	delete third;
}