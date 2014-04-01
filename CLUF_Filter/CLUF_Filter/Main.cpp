#include <iostream>

#include "Filter.h"

int main()
{
	Filter fileFilter("test.txt");

	fileFilter.ReadFile();
	fileFilter.FilterFile("sad");

	auto filtered = fileFilter.GetFilteredFile();
	for (auto line = filtered.begin(); line != filtered.end(); ++line)
	{
		std::cout << (*line) << '\n';
	}
}