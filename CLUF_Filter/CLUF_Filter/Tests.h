#ifndef _CLUF__TESTS_H
#define _CLUF__TESTS_H


#include "FilterChain.h"
#include "WordFilter.h"
#include "CapitalizeFilter.h"
#include "Escaper.h"
#include "Codec.h"

#include <iostream>
#include <sstream>
#include <algorithm>

extern const char *TEST_FILE_NAME;


//////////////////////////
//  Filter Chain tests  //
//////////////////////////

bool Test_FilterChainCreation(const std::string &inputFile, const std::string &outputFile);

bool Test_FilterChainAddFilter(Filter *filter, int filterID);

bool Test_FilterChainRemoveFilter(FilterChain *chain, int filterID);

bool Test_FilterChainSerialization(const FilterChain &chain, const std::string &fileName);

bool Test_FilterChainProcessThroughFilters(FilterChain &chain, const std::string &expectedOutput);

///////////////////////////
//  Encode Filter tests  //
///////////////////////////

bool Test_WordFilter(const WordFilter &filter, const std::string &inputText,
				     const std::string &outputText);

///////////////////////////
//  Encode Filter tests  //
///////////////////////////

bool Test_EncodeFilterEncoding(const EncodeFilter &filter, const std::string &inputText,
							   const std::string &outputText);

///////////////////////////
//  Decode Filter tests  //
///////////////////////////

bool Test_DecodeFilterDecoding(const DecodeFilter &filter, const std::string &inputText,
							   const std::string &verifyingText);

///////////////////////////////
//  Capitalize Filter tests  //
///////////////////////////////

bool Test_CapitalizeFilter(const CapitalizeFilter &filter, const std::string &inputText,
						   const std::string &verifyingText);

////////////////////////////////
//  Zero Escape Filter tests  //
////////////////////////////////

bool Test_ZeroEscapeFilter(const ZeroEscapeFilter &filter, const std::string &inputText,
						   const std::string &verifyingText);

//////////////////////////////////
//  Zero Unescape Filter tests  //
//////////////////////////////////

bool Test_ZeroUnescapeFilter(const ZeroUnescapeFilter &filter, const std::string &inputText,
					  	     const std::string &verifyingText);


#endif