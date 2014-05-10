#include <iostream>

#include "TestSuite.h"
#include "Tests.h"

template <class T>
std::string VectorToString(const std::vector<T> &vect)
{
	std::stringstream streamedVector;
	for (auto elem : vect)
	{
		streamedVector << "\"" << elem << "\", ";
	}
	return streamedVector.str();
}

int main()
{
	TestSuite testSuite;

	/////////////////////////////////////////////////////////////////////////////////////////////////

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

	/////////////////////////////////////////////////////////////////////////////////////////////////

	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterChainCreation('" << TEST_FILE_NAME << "', '" << TEST_FILE_NAME << "')";
	testSuite.AddFunction(funcName.str(), 
						  std::bind(Test_FilterChainCreation, TEST_FILE_NAME, TEST_FILE_NAME));

	std::string newFilterExpr = "labadidula'' ";
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterChainAddFilter('" << newFilterExpr << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterChainAddFilter, newFilterExpr));

	std::vector<std::string> filterExpressions;
	filterExpressions.push_back("inform");
	filterExpressions.push_back("c''sii\'\"  ");
	filterExpressions.push_back("\0I'm SOO NULL\0"); // To add or not to add? Nah... Won't bother.
	filterExpressions.push_back("peshoo");
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterChainAddFilters('" << VectorToString(filterExpressions) << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterChainAddFilters, filterExpressions));

	FilterChain newChain(TEST_FILE_NAME, TEST_FILE_NAME);
	newChain.AddFilter("saddden");
	newChain.AddFilter("room for 'two'");
	FilterChain expectedChain(TEST_FILE_NAME, TEST_FILE_NAME);
	expectedChain.AddFilter("room for 'two'");
	std::string exprToRem = "saddden";
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterChainRemoveFilter('" << VectorToString(newChain.GetFilters()) << "', '"  
			 << exprToRem << "', '" << VectorToString(expectedChain.GetFilters()) << "')";
	testSuite.AddFunction(funcName.str(), 
					      std::bind(Test_FilterChainRemoveFilter, newChain, exprToRem, expectedChain));

	std::string fileName = "testSAD.txt";
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterChainSerialization('" << VectorToString(newChain.GetFilters()) << "', '"  
			 << fileName << "')";
	testSuite.AddFunction(funcName.str(), std::bind(Test_FilterChainSerialization, newChain, fileName));

	///
	/// Untestable due to some strange behavior of std::bind
	/// The copy ctor of FilterChain isn't invoked properly? The file names aren't copied.
	/// ^^^^
	/// |||| Disregard! NEVER BLAME THE LIBRARY!!!
	///
	FilterChain otherChain("back.txt", "oback.txt");
	otherChain.AddFilter("room for 'two'");
	std::string expectedOutput = "there is always room for 'two'\n";
	funcName.str(std::string());
	funcName.clear();
	funcName << "Test_FilterChainProcessThroughFilters('" << VectorToString(otherChain.GetFilters()) << "', '"  
			 << expectedOutput << "')";
	testSuite.AddFunction(funcName.str(), 
						  std::bind(Test_FilterChainProcessThroughFilters, otherChain, expectedOutput));

	/////////////////////////////////////////////////////////////////////////////////////////////////

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