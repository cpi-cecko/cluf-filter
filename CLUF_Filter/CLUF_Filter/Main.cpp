#include <iostream>

#include "TestSuite.h"
#include "Tests.h"

int main()
{
	TestSuite testSuite;

	std::string filterExpr = "";
	std::string text = "";
	std::string expectedText = "";
	std::stringstream funcName;
	funcName << "Test_FilterText('" << filterExpr << "', '" 
			 << text << "', '" << expectedText << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterText, filterExpr, text, expectedText));

	Filter testFilter("bogo Fogo");
	std::string expected = "bogo Fogo";
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterAssignment('" << testFilter.GetFilterExpression() 
		     << "', '" << expected << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterAssignment, testFilter, expected));

	Filter second("fogo");
	bool expectedEq = false;
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterEquality('" << testFilter.GetFilterExpression() << "', '" 
			 << second.GetFilterExpression() << "', '" << expectedEq << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterEquality, testFilter, second, expectedEq));

	expectedEq = true;
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterInequality('" << testFilter.GetFilterExpression() << "', '" 
			 << second.GetFilterExpression() << "', '" << expectedEq << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterInequality, testFilter, second, expectedEq));

	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterOutput('" << testFilter.GetFilterExpression() << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterOutput, testFilter));

	std::string expressionToPut = "I'm here";
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterInput('" << expressionToPut << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterInput, expressionToPut));

	char chToConcat = 'a';
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterCharConcat('" << testFilter.GetFilterExpression() << "', '" 
			 << chToConcat << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterCharConcat, testFilter, chToConcat));

	std::string strToConcat = "abcdef";
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterStringConcat('" << testFilter.GetFilterExpression() << "', '" 
			 << strToConcat << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterStringConcat, testFilter, strToConcat.c_str()));

	Filter otherFilter("newChain");
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterChainCreation('" << testFilter.GetFilterExpression() << "', '" 
			 << otherFilter.GetFilterExpression() << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterChainOpCreation, testFilter, otherFilter));

	/*
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterEquality('" << testFilter.GetFilterExpression() << "', '" 
			 << second.GetFilterExpression() << "', '" << expectedEq;
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterEquality, testFilter, second, expectedEq));

	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterEquality('" << testFilter.GetFilterExpression() << "', '" 
			 << second.GetFilterExpression() << "', '" << expectedEq;
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterEquality, testFilter, second, expectedEq));
	*/

	testSuite.RunTests();

	//{
	//	FilterChain testChain("test.txt", "filtered.txt");
	//	testChain.AddFilter("pony");
	//	testChain.AddFilter("sad");

	//	testChain.ProcessThroughFilters();

	//	testChain.Serialize("serialize.txt");
	//}

	//FilterChain newChain;
	//newChain.Deserialize("serialize.txt");

	//newChain.AddFilter("Why");
	//newChain.ProcessThroughFilters();

	return 0;
}