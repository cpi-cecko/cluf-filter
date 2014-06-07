#ifndef _CLUF__FILTER_CHAIN_H
#define _CLUF__FILTER_CHAIN_H

#include <fstream>
#include <vector>
#include <memory>

#include "Filter.h"

class FilterChain
{
private:
	std::ifstream inputFile; /// @property inputFile - the file which we'll filter
	std::ofstream outputFile; /// @property outputFile - the file which we'll output the filtered text to
	std::string inputFileName; /// @property inputFileName - the name of the inputFile
	std::string outputFileName; /// @property outputFileName - the name of the outputFile
	std::vector<Filter*> filters; /// @property filters - an array of conequentially applied filters

public:
	///
	/// @brief Constructs the FilterChain object and opens the input/output files.
	/// 
	FilterChain(const std::string &newInputFileName, const std::string &newOutputFileName);
	explicit FilterChain() : inputFileName(""), outputFileName("") {}
	///
	/// @brief Closes the files opened by the FilterChain instance.
	///
	~FilterChain();

	///
	/// @brief Adds a filter to the filter chain.
	///
	void AddFilter(Filter *newFilter);
	/// 
	/// @brief Removes a filter from the filter chain.
	///
	void RemoveFilter(const std::string &filterExpression);

	///
	/// @brief Returns the chain's filters
	///
	const std::vector<Filter*>& GetFilters() const;

	///
	/// @brief Serializes the FilterChain instance
	///
	void Serialize(const std::string &fileName) const;
	///
	/// @brief Deserializes the FilterChain instance
	///
	void Deserialize(const std::string &fileName);

	///
	/// @brief Consequentially applies the stored filters to the inputFile and outputs the result
	///		   to the ouptutFile
	///
	void ProcessThroughFilters();

	///
	/// @brief Opens the input file if such wasn't opened before. Used after operator| for Filter.
	///
	void OpenInputFile(const std::string &newInputFileName);
	///
	/// @brief Opens the output file if such wasn't opened before. Used after operator| for Filter.
	///
	void OpenOutputFile(const std::string &newOutputFileName);

#ifndef BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
private:
	/// Locked assignment operator and copy constructor to prevent dangerous initialization of
	/// FilterChain instances
#endif
	///
	/// @brief Copy constructor
	///
	FilterChain(const FilterChain &other);
	///
	/// @brief Assignment operator
	///
	FilterChain& operator=(const FilterChain &other);

public:
	friend bool Test_FilterChainCreation(const std::string&, const std::string&);
	friend bool Test_FilterChainSerialization(const FilterChain &chain, const std::string &fileName);
	friend bool Test_FilterChainProcessThroughFilters(FilterChain &chain, const std::string &expectedOutput);
	friend bool Test_FilterChainFilterAdd(const Filter *filterToTest);
};


#endif