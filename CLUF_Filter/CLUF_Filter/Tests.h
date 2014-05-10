#ifndef _CLUF__TESTS_H
#define _CLUF__TESTS_H


#include "FilterChain.h"

#include <iostream>
#include <sstream>
#include <algorithm>

extern const char *TEST_FILE_NAME;


////////////////////
//  Filter tests  //
////////////////////
bool Test_FilterText(const std::string &filterExpr, std::string &text, 
				     const std::string &expectedText);

bool Test_FilterAssignment(const Filter &toAssign, const std::string &expectedExpression);

bool Test_FilterEquality(const Filter &first, const Filter &second, bool expectedEq);

bool Test_FilterInequality(const Filter &first, const Filter &second, bool expectedEq);

bool Test_FilterOutput(const Filter &filterToWrite);
bool Test_FilterInput(const std::string &expressionToPut);

bool Test_FilterCharConcat(Filter &filter, char ch);
bool Test_FilterStringConcat(Filter &filter, const char *str);

bool Test_FilterChainOpCreation(const Filter &lhs, const Filter &rhs);

//////////////////////////
//  Filter Chain tests  //
//////////////////////////

bool Test_FilterChainCreation(const std::string &inputFile, const std::string &outputFile);

bool Test_FilterChainAddFilter(const std::string &filterExpression);
bool Test_FilterChainAddFilters(const std::vector<std::string> &filterExpressions);

bool Test_FilterChainRemoveFilter(FilterChain &chain, const std::string &filterExprToRemove,
								  const FilterChain &expectedChain);

bool Test_FilterChainSerialization(const FilterChain &chain, const std::string &fileName);

bool Test_FilterChainProcessThroughFilters(FilterChain &chain, const std::string &expectedOutput);

bool Test_FilterChainCopyFrom(const FilterChain &toCopyFrom);
bool Test_FilterChainEqualOp(const FilterChain &toEqualTo);
bool Test_FilterChainCopyCtor(const FilterChain &toCopyCtor);

bool Test_FilterChainEquality(const FilterChain &lhs, const FilterChain &rhs, bool expectedEq);
bool Test_FilterChainInequality(const FilterChain &lhs, const FilterChain &rhs, bool expectedEq);

bool Test_FilterChainFilterAdd(const Filter &filterToTest);

bool Test_FilterChainRemoveFilterByString(FilterChain &testChain, const char *str);

bool Test_FilterChainIdxOperator(const FilterChain &chain, int idx, const std::string &expectedExpr);
bool Test_FilterChainStrOperator(const FilterChain &chain, const char *str, const std::string &expectedExpr);

bool Test_FilterChainOperatorAddFilterToChain(const FilterChain &chain, const Filter &filter,
											  const FilterChain &expectedChain);

bool Test_FilterChainOperatorCombineChains(const FilterChain &lhs, const FilterChain &rhs,
										   const FilterChain &expectedChain);


#endif