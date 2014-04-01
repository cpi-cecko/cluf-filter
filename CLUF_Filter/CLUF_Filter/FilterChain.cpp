#include "FilterChain.h"

#include <iostream>

FilterChain::FilterChain(const std::string &newInputFileName, const std::string &newOutputFileName)
	: inputFile(newInputFileName), outputFile(newOutputFileName),
	  inputFileName(newInputFileName), outputFileName(newOutputFileName), filters()
{
}
FilterChain::~FilterChain()
{
	inputFile.close();
	outputFile.close();
}

void FilterChain::AddFilter(const std::string &filterExpression)
{
	filters.push_back(Filter(filterExpression));
}
void FilterChain::RemoveFilter(const std::string &filterExpression)
{
	for (auto filter = filters.begin(); filter != filters.end(); ++filter)
	{
		if (filter->GetFilterExpression() == filterExpression)
		{
			filters.erase(filter);
			return;
		}
	}

	std::cerr << "Filter with filter expression `" << filterExpression << "' not found\n";
}

void FilterChain::Serialize(const std::string &fileName) const
{
	std::ofstream serializationFile(fileName, std::ios::trunc | std::ios::binary);

	serializationFile << inputFileName;
	serializationFile << outputFileName;
	serializationFile << filters.size();
	for (auto filter = filters.begin(); filter != filters.end(); ++filter)
	{
		serializationFile << filter->GetFilterExpression();
	}

	serializationFile.close();
}
void FilterChain::Desearialize(const std::string &fileName)
{
	std::ifstream serializationFile(fileName, std::ios::binary);

	serializationFile >> inputFileName;
	inputFile.open(inputFileName);
	serializationFile >> outputFileName;
	outputFile.open(outputFileName);
	
	int filtersSize = 0;
	serializationFile >> filtersSize;
	for (int i = 0; i < filtersSize; i++)
	{
		std::string filterExpression = "";
		serializationFile >> filterExpression;
		AddFilter(filterExpression);
	}

	serializationFile.close();
}

void FilterChain::ProcessThroughFilters()
{
	std::stringstream fileStream;
	fileStream << inputFile.rdbuf();

	for (auto filter = filters.begin(); filter != filters.end(); ++filter)
	{
		filter->FilterStream(fileStream);
	}

	outputFile << fileStream.str();
}