#include <iostream>

#include "Filter.h"

int main()
{
	Filter fileFilter("test.txt");

	fileFilter.ReadFile();
	fileFilter.OutputFilterWord("sad");
}