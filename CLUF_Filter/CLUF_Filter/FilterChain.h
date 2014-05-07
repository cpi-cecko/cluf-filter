#ifndef _CLUF__FILTER_CHAIN_H
#define _CLUF__FILTER_CHAIN_H

#include <fstream>
#include <vector>

#include "Filter.h"

class FilterChain
{
private:
	std::ifstream inputFile; /// @property inputFile - the file which we'll filter
	std::ofstream outputFile; /// @property outputFile - the file which we'll output the filtered text to
	std::string inputFileName; /// @property inputFileName - the name of the inputFile
	std::string outputFileName; /// @property outputFileName - the name of the outputFile
	std::vector<Filter> filters; /// @property filters - an array of conequentially applied filters

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
	void AddFilter(const std::string &filterExpression);
	/// 
	/// @brief Removes a filter from the filter chain.
	///
	void RemoveFilter(const std::string &filterExpression);

	///
	/// @brief Returns the chain's filters
	///
	const std::vector<Filter>& GetFilters() const;

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

public:
#ifdef BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
	///
	/// @brief Method to copy the containts of another FilterChain into this FilterChain
	///
	void CopyFrom(const FilterChain &other);
#endif

public:
	///
	/// @brief Compares two FilterChains based on their Filters
	/// @return true if the Filters are equal
	///
	bool operator==(const FilterChain &other) const;
	///
	/// @brief Compares two FilterChains based on their Filters
	/// @return true if the Filters are different
	///
	bool operator!=(const FilterChain &other) const;

	///
	/// @brief Adds a filter to filters
	///
	FilterChain& operator+=(const Filter &filterToAdd);
	///
	/// @brief Removes filters which contain `str' in them
	///
	FilterChain& operator-=(const char *str);

	///
	/// @brief Returns a filter at the given index
	///
	Filter operator[](int idx) const;
	///
	/// @brief Returns a filter which filters the given string
	///
	Filter operator[](const char *str) const;

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
};

#ifdef BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
///
/// @brief Adds a Filter to the given FilterChain
///
FilterChain operator|(const FilterChain &chain, const Filter &filter);
///
/// @brief Concatenates the two given FilterChains. The new FilterChain has unique filters.
///
FilterChain operator+(const FilterChain &lhs, const FilterChain &rhs);
#endif

#endif