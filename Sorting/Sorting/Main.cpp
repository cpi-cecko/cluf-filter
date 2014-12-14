#include <iostream>

#include "SortTester.h"

int main()
{
	SorterImplementation<int> *sorters[] = 
	{
		new QuickSorter<int>()
	};

	MySortTester<int> myTester(sorters, 1);
	myTester.GetSummary(std::cout);

	return 0;
}