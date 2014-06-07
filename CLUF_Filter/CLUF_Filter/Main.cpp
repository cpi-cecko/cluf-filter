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

	//std::stringstream funcName;
	//funcName.str(std::string());
	//funcName.clear();
	//funcName << "Test_FilterChainCreation('" << TEST_FILE_NAME << "', '" << TEST_FILE_NAME << "')";
	//testSuite.AddFunction(funcName.str(), 
	//					  std::bind(Test_FilterChainCreation, TEST_FILE_NAME, TEST_FILE_NAME));

	//std::string newFilterExpr = "labadidula'' ";
	//funcName.str(std::string());
	//funcName.clear();
	//funcName << "Test_FilterChainAddFilter('" << newFilterExpr << "')";
	//testSuite.AddFunction(funcName.str(), std::bind(Test_FilterChainAddFilter, newFilterExpr));

	//std::vector<std::string> filterExpressions;
	//filterExpressions.push_back("inform");
	//filterExpressions.push_back("c''sii\'\"  ");
	//filterExpressions.push_back("\0I'm SOO NULL\0"); // To add or not to add? Nah... Won't bother.
	//filterExpressions.push_back("peshoo");
	//funcName.str(std::string());
	//funcName.clear();
	//funcName << "Test_FilterChainAddFilters('" << VectorToString(filterExpressions) << "')";
	//testSuite.AddFunction(funcName.str(), std::bind(Test_FilterChainAddFilters, filterExpressions));

	//FilterChain newChain(TEST_FILE_NAME, TEST_FILE_NAME);
	//FilterChain expectedChain(TEST_FILE_NAME, TEST_FILE_NAME);
	//expectedChain.AddFilter("room for 'two'");
	//std::string exprToRem = "saddden";
	//funcName.str(std::string());
	//funcName.clear();
	//funcName << "Test_FilterChainRemoveFilter('" << VectorToString(newChain.GetFilters()) << "', '"  
	//		 << exprToRem << "', '" << VectorToString(expectedChain.GetFilters()) << "')";
	//testSuite.AddFunction(funcName.str(), 
	//				      std::bind(Test_FilterChainRemoveFilter, newChain, exprToRem, expectedChain));

	//std::string fileName = "testSAD.txt";
	//funcName.str(std::string());
	//funcName.clear();
	//funcName << "Test_FilterChainSerialization('" << VectorToString(newChain.GetFilters()) << "', '"  
	//		 << fileName << "')";
	//testSuite.AddFunction(funcName.str(), std::bind(Test_FilterChainSerialization, newChain, fileName));

	///
	/// Untestable due to some strange behavior of std::bind
	/// The copy ctor of FilterChain isn't invoked properly? The file names aren't copied.
	/// ^^^^
	/// |||| Disregard! NEVER BLAME THE LIBRARY!!!
	///
	//FilterChain otherChain("back.txt", "oback.txt");
	//otherChain.AddFilter("room for 'two'");
	//std::string expectedOutput = "there is always room for 'two'\n";
	//funcName.str(std::string());
	//funcName.clear();
	//funcName << "Test_FilterChainProcessThroughFilters('" << VectorToString(otherChain.GetFilters()) << "', '"  
	//		 << expectedOutput << "')";
	//testSuite.AddFunction(funcName.str(), 
	//					  std::bind(Test_FilterChainProcessThroughFilters, otherChain, expectedOutput));

	/////////////////////////////////////////////////////////////////////////////////////////////////

	testSuite.RunTests();

	return 0;
}