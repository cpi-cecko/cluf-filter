#include <iostream>

#include "FilterChain.h"

int main()
{
	FilterChain testChain("test.txt", "filtered.txt");
	testChain.AddFilter("pony");
	testChain.AddFilter("sad");

	testChain.ProcessThroughFilters();

	return 0;
}