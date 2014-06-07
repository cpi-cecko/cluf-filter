#include "Tests.h"

const char *TEST_FILE_NAME = "test.txt";


//////////////////////////
//  Filter Chain tests  //
//////////////////////////

bool Test_FilterChainCreation(const std::string &inputFile, const std::string &outputFile)
{
	FilterChain testChain(inputFile, outputFile);
	return testChain.inputFile.is_open() && testChain.outputFile.is_open();
}

//bool Test_FilterChainAddFilter(const std::string &filterExpression)
//{
//	FilterChain testChain(TEST_FILE_NAME, TEST_FILE_NAME);
//	testChain.AddFilter(filterExpression);	
//
//	return testChain.GetFilters()[0].GetFilterExpression() == filterExpression;
//}
//bool Test_FilterChainAddFilters(const std::vector<std::string> &filterExpressions)
//{
//	FilterChain testChain(TEST_FILE_NAME, TEST_FILE_NAME);
//	for (auto expr : filterExpressions)
//	{
//		testChain.AddFilter(expr);
//	}
//
//	auto filters = testChain.GetFilters();
//	if (filters.size() != filterExpressions.size())
//	{
//		return false;
//	}
//	for (size_t idx = 0; idx < filters.size(); ++idx)
//	{
//		if (filters[idx].GetFilterExpression() != filterExpressions[idx])
//		{
//			return false;
//		}
//	}
//
//	return true;
//}

//bool Test_FilterChainRemoveFilter(FilterChain &chain, const std::string &filterExprToRemove,
//								  const FilterChain &expectedChain)
//{
//	chain.RemoveFilter(filterExprToRemove);
//	return chain == expectedChain;
//}

bool Test_FilterChainSerialization(const FilterChain &chain, const std::string &fileName)
{
	chain.Serialize(fileName);

	FilterChain newChain;
	newChain.Deserialize(fileName);

	if (chain.inputFileName == newChain.inputFileName &&
		chain.outputFileName == newChain.outputFileName &&
		chain.filters == newChain.filters)
	{
		return true;
	}
	return false;
}

bool Test_FilterChainProcessThroughFilters(FilterChain &chain, const std::string &expectedOutput)
{
	chain.ProcessThroughFilters();
	std::ifstream filteredFile(chain.outputFileName);
	std::stringstream fileStream;
	fileStream << filteredFile.rdbuf(); 
	std::string stringedStream = fileStream.str();
	filteredFile.close();
	return stringedStream == expectedOutput;
}