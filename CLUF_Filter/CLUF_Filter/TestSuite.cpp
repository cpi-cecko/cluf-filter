#include "TestSuite.h"

#include <iostream>
#include <string>

void TestSuite::AddFunction(const std::string &functionName, TestFunction func)
{
	tests.insert(std::make_pair(functionName, func));
}

void TestSuite::RunTests()
{
	for (auto test : tests)
	{
		if (test.second())
		{
			passedTests++;
			std::cout << "Passed test: " << test.first << std::endl;
		}
		else
		{
			failedTests++;
			std::cout << "**Failed** test: " << test.first << std::endl;
		}
	}
}