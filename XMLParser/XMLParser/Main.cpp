#include <iostream>

#include "../Tree/Tree.h"


int main()
{
	Tree<int> sampleTree;

	sampleTree.Insert("root/123/my/13/", 5);
	sampleTree.Insert("root/123/my/14/", 6);
	sampleTree.Insert("root/123/az", 7);
	sampleTree.Insert("root/123/az", 8);

	//Result<int> valAtAz = sampleTree.At("root/123/az");
	//if (valAtAz.isValid)
	//	std::cout << valAtAz.val[0];

	return 0;
}