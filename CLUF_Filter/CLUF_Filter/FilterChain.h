#ifndef _CLUF__FILTER_CHAIN_H
#define _CLUF__FILTER_CHAIN_H

#include <fstream>
#include <vector>

#include "Filter.h"

class FilterChain
{
private:
	std::ifstream inputFile;
	std::ofstream outputFile;
	std::string inputFileName;
	std::string outputFileName;
	std::vector<Filter> filters;

public:
	FilterChain(const std::string &newInputFileName, const std::string &newOutputFileName);
	~FilterChain();

	void AddFilter(const std::string &filterExpression);
	void RemoveFilter(const std::string &filterExpression);

	void Serialize(const std::string &fileName) const;
	void Desearialize(const std::string &fileName);

	void ProcessThroughFilters();
};

#endif