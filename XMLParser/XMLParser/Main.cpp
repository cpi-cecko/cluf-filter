#include <iostream>

#include "../Tree/Tree.h"


void PrettyPrint(TreeIterator<int> &iter)
{
	std::cout << "<" << iter.Deref()->GetKey() << ">\n";
	if (iter.Deref()->HasVal())
	{
		std::cout << "  " << *iter.Deref()->GetVal() << '\n';
	}
	if (iter.HasChild()) 
	{
		PrettyPrint(iter.Child());
	}
	std::cout << "</" << iter.Deref()->GetKey() << ">\n";

	while (iter.HasNext())
	{
		PrettyPrint(iter.Next());
	}
}

int main()
{
	Tree<int> testTree;
	testTree.Insert("root/1", 1);
	testTree.Insert("root/2", 2);
	testTree.Insert("root/3", 3);
	testTree.Insert("root/3", 3);
	testTree.Insert("root/1/2/3", 123);
	testTree.Insert("root/2/3/4", 234);
	testTree.Insert("root/4", 4);

	testTree.Insert("another/deep1", 1);
	testTree.Insert("another/deep1/deep2", 12);
	testTree.Insert("another/deep2", 2);
	testTree.Insert("another/deep3/deep4/deeper", 4);

	testTree.Insert("contact/person/name", 1);
	testTree.Insert("contact/person/name", 2);
	testTree.Insert("contact/person/email", 3);
	testTree.Insert("contact/person", 1);
	testTree.Insert("contact/person/name", 5);
	testTree.Insert("contact/person/email", 3);

	TreeIterator<int> iter = testTree.GetBeginIter();
	PrettyPrint(iter.Child());

	return 0;
}