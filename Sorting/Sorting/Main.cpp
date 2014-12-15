#include <iostream>

#include "SortTester.h"

int main()
{
	SorterImplementation<int> *sorters[] = 
	{
		new InsertionSorter<int>(),
		new QuickSorter<int>(),
		new MergeSorter<int>(),
		new HeapSorter<int>(),
		new SelectionSorter<int>()
	};

	MySortTester<int> myTester(sorters, 5);
	myTester.GetSummary(std::cout);

	return 0;
}