#ifndef _CLUF__TEST_SUITE_H
#define _CLUF__TEST_SUITE_H


#include <functional>
#include <map>

class TestSuite
{
public:
	typedef std::function<bool()> TestFunction;
	typedef std::map<std::string, TestFunction> TestFunctionsMap;

private:
	TestFunctionsMap tests;
	size_t passedTests;
	size_t failedTests;

public:
	TestSuite() : passedTests(0), failedTests(0) {}

	void AddFunction(const std::string &functionName, TestFunction func);

	void RunTests();
};


#endif