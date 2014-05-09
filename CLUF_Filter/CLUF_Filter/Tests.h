#ifndef _CLUF__TESTS_H
#define _CLUF__TESTS_H


#include "FilterChain.h"

#include <iostream>
#include <sstream>
#include <algorithm>

const char *TEST_FILE_NAME = "test.txt";


////////////////////
//  Filter tests  //
////////////////////
bool Test_FilterText(const std::string &filterExpr, std::string &text, 
				     const std::string &expectedText)
{
	Filter filter(filterExpr);
	filter.FilterText(text);
	return text == expectedText;
}

bool Test_FilterAssignment(const Filter &toAssign, const std::string &expectedExpression)
{
	Filter newFilter = toAssign;
	return newFilter.GetFilterExpression() == expectedExpression;
}

bool Test_FilterEquality(const Filter &first, const Filter &second, bool expectedEq)
{
	bool isEq = first == second;
	return isEq == expectedEq;
}

bool Test_FilterInequality(const Filter &first, const Filter &second, bool expectedEq)
{
	bool isEq = first != second;
	return isEq == expectedEq;
}

bool Test_FilterOutput(const Filter &filterToWrite)
{
	std::stringstream strStream;
	strStream << filterToWrite;
	return strStream.str() == filterToWrite.GetFilterExpression();
}
bool Test_FilterInput(const std::string &expressionToPut)
{
	std::stringstream strStream;
	strStream << expressionToPut;

	Filter newFilter("");
	strStream >> newFilter;

	return expressionToPut == newFilter.GetFilterExpression();
}

bool Test_FilterCharConcat(Filter &filter, char ch)
{
	std::string expressionBefore = filter.GetFilterExpression();
	filter += ch;
	return filter.GetFilterExpression() == (expressionBefore + ch);
}
bool Test_FilterStringConcat(Filter &filter, const char *str)
{
	std::string expressionBefore = filter.GetFilterExpression();
	filter += str;
	return filter.GetFilterExpression() == (expressionBefore + str);
}

bool Test_FilterChainOpCreation(const Filter &lhs, const Filter &rhs)
{
	FilterChain newChain = lhs | rhs;
	bool isSizeTwo = newChain.GetFilters().size() == 2;
	auto filters = newChain.GetFilters();
	if (filters[0].GetFilterExpression() != lhs.GetFilterExpression())
	{
		return false;
	}
	if (filters[1].GetFilterExpression() != rhs.GetFilterExpression())
	{
		return false;
	}
	return isSizeTwo;
}

//////////////////////////
//  Filter Chain tests  //
//////////////////////////

bool Test_FilterChainCreation(const std::string &inputFile, const std::string &outputFile)
{
	FilterChain testChain(inputFile, outputFile);
	return testChain.inputFile.is_open() && testChain.outputFile.is_open();
}

bool Test_FilterChainAddFilter(const std::string &filterExpression)
{
	FilterChain testChain(TEST_FILE_NAME, TEST_FILE_NAME);
	testChain.AddFilter(filterExpression);	

	return testChain.GetFilters()[0].GetFilterExpression() == filterExpression;
}
bool Test_FilterChainAddFilters(const std::vector<std::string> &filterExpressions)
{
	FilterChain testChain(TEST_FILE_NAME, TEST_FILE_NAME);
	for (auto expr : filterExpressions)
	{
		testChain.AddFilter(expr);
	}

	auto filters = testChain.GetFilters();
	if (filters.size() != filterExpressions.size())
	{
		return false;
	}
	for (size_t idx = 0; idx < filters.size(); ++idx)
	{
		if (filters[idx].GetFilterExpression() != filterExpressions[idx])
		{
			return false;
		}
	}

	return true;
}

bool Test_FilterChainRemoveFilter(FilterChain &chain, const std::string &filterExprToRemove,
								  const FilterChain &expectedChain)
{
	chain.RemoveFilter(filterExprToRemove);
	return chain == expectedChain;
}

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
	std::stringstream fileStream;
	fileStream << chain.outputFile.rdbuf(); 
	std::string stringedStream = fileStream.str();
	return stringedStream == expectedOutput;
}

bool Test_FilterChainCopyFrom(const FilterChain &toCopyFrom)
{
	FilterChain newChain;
	newChain.CopyFrom(toCopyFrom);

	return newChain == toCopyFrom;
}
bool Test_FilterChainEqualOp(const FilterChain &toEqualTo)
{
	FilterChain newChain;
	newChain = toEqualTo;

	return newChain == toEqualTo;
}
bool Test_FilterChainCopyCtor(const FilterChain &toCopyCtor)
{
	FilterChain newChain(toCopyCtor);

	return newChain == toCopyCtor;
}

bool Test_FilterChainEquality(const FilterChain &lhs, const FilterChain &rhs, bool expectedEq)
{
	bool isEq = lhs == rhs;
	return isEq == expectedEq;
}
bool Test_FilterChainInequality(const FilterChain &lhs, const FilterChain &rhs, bool expectedEq)
{
	bool isEq = lhs != rhs;
	return isEq == expectedEq;
}

bool Test_FilterChainFilterAdd(const Filter &filterToTest)
{
	FilterChain newChain(TEST_FILE_NAME, TEST_FILE_NAME);
	newChain += filterToTest;

	return newChain.filters.back() == filterToTest;
}

bool Test_FilterChainRemoveFilterByString(const char *str)
{
	FilterChain newChain(TEST_FILE_NAME, TEST_FILE_NAME);
	newChain -= str;

	auto chainFilters = newChain.GetFilters();
	auto elem = std::find_if(chainFilters.begin(), chainFilters.end(), 
							[&str](const Filter &filter)
							{
								auto filterExpr = filter.GetFilterExpression();
								return filterExpr.find(str) != filterExpr.npos;
							});

	return elem == chainFilters.end();
}

bool Test_FilterChainIdxOperator(const FilterChain &chain, int idx, const std::string &expectedExpr)
{
	return chain[idx].GetFilterExpression() == expectedExpr;
}
bool Test_FilterChainStrOperator(const FilterChain &chain, const char *str, const std::string &expectedExpr)
{
	return chain[str].GetFilterExpression() == expectedExpr;
}

bool Test_FilterChainOperatorAddFilterToChain(const FilterChain &chain, const Filter &filter,
											  const FilterChain &expectedChain)
{
	FilterChain newChain(TEST_FILE_NAME, TEST_FILE_NAME);
	newChain = chain | filter;
	return newChain == expectedChain;
}

bool Test_FilterChainOperatorCombineChains(const FilterChain &lhs, const FilterChain &rhs,
										   const FilterChain &expectedChain)
{
	FilterChain testChain(TEST_FILE_NAME, TEST_FILE_NAME);
	testChain = lhs + rhs;
	return testChain == expectedChain;
}


#endif