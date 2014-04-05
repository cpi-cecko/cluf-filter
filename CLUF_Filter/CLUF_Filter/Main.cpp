#include <iostream>

#include "FilterChain.h"

int main()
{
	{
		FilterChain testChain("test.txt", "filtered.txt");
		testChain.AddFilter("pony");
		testChain.AddFilter("sad");

		testChain.ProcessThroughFilters();

		testChain.Serialize("serialize.txt");
	}

	FilterChain newChain;
	newChain.Desearialize("serialize.txt");

	newChain.AddFilter("Why");
	newChain.ProcessThroughFilters();

	return 0;
}