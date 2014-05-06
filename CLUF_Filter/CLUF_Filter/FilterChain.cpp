#include "FilterChain.h"

#include <iostream>
#include <sstream>

FilterChain::FilterChain(const std::string &newInputFileName, const std::string &newOutputFileName)
	: inputFile(newInputFileName), outputFile(newOutputFileName, std::ios::trunc),
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

	std::cerr << "Error: Filter with filter expression `" << filterExpression << "' not found\n";
}

void FilterChain::Serialize(const std::string &fileName) const
{
	std::ofstream serializationFile(fileName, std::ios::trunc | std::ios::binary);

	if (serializationFile.is_open())
	{
		size_t inputFileStrLength = inputFileName.length();
		serializationFile.write((char*)&inputFileStrLength, sizeof(size_t));
		serializationFile.write(inputFileName.c_str(), inputFileName.length() * sizeof(char));
		size_t outputFileStrLength = outputFileName.length();
		serializationFile.write((char*)&outputFileStrLength, sizeof(size_t));
		serializationFile.write(outputFileName.c_str(), outputFileName.length() * sizeof(char));
		size_t filtersSize = filters.size();
		serializationFile.write((char*)&filtersSize, sizeof(size_t));
		for (auto filter = filters.begin(); filter != filters.end(); ++filter)
		{
			std::string filterExpression = filter->GetFilterExpression();
			size_t filterExpressionLength = filterExpression.length();
			serializationFile.write((char*)&filterExpressionLength, sizeof(size_t));
			serializationFile.write(filterExpression.c_str(), filterExpressionLength * sizeof(char));
		}
	}
	else
	{
		std::cerr << "Error: Unable to open serialization file.\n";
	}

	serializationFile.close();
}
void FilterChain::Deserialize(const std::string &fileName)
{
	std::ifstream serializationFile(fileName, std::ios::binary);

	if (serializationFile.is_open())
	{
		size_t inputFileNameLength = 0;
		serializationFile.read((char*)&inputFileNameLength, sizeof(size_t));
		char strInputFileName[30] = "";
		serializationFile.read((char*)&strInputFileName, inputFileNameLength * sizeof(char));
		inputFileName.append(strInputFileName);
		inputFile.open(inputFileName);

		size_t outputFileNameLength = 0;
		serializationFile.read((char*)&outputFileNameLength, sizeof(size_t));
		char strOutputFileName[30] = "";
		serializationFile.read((char*)&strOutputFileName, outputFileNameLength * sizeof(char));
		outputFileName.append(strOutputFileName);
		outputFile.open(outputFileName);
		
		int filtersSize = 0;
		serializationFile.read((char*)&filtersSize, sizeof(int));
		for (int i = 0; i < filtersSize; i++)
		{
			size_t filterExpressionLength = 0;
			serializationFile.read((char*)&filterExpressionLength, sizeof(size_t));
			char filterExpression[100] = "";
			serializationFile.read((char*)&filterExpression, filterExpressionLength * sizeof(char));
			AddFilter(filterExpression);
		}
	}
	else
	{
		std::cerr << "Error: Unable to open deserialization file.\n";
	}

	serializationFile.close();
}

void FilterChain::ProcessThroughFilters()
{
	if (inputFile.is_open() && outputFile.is_open())
	{
		std::stringstream fileStream;
		fileStream << inputFile.rdbuf();
		std::string filteredText = fileStream.str();

		for (auto filter = filters.begin(); filter != filters.end(); ++filter)
		{
			filter->FilterText(filteredText);
		}

		outputFile << filteredText;
	}
	else
	{
		std::cerr << "Error: Unable to open input or output file.\n";
	}
}

#ifdef BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
FilterChain::FilterChain(const FilterChain &other)
{
	if (this != &other)
	{
		FilterChain(other.inputFileName, other.outputFileName);
		for (auto filter = other.filters.begin(); filter != other.filters.end(); ++filter)
		{
			AddFilter(filter->GetFilterExpression());
		}
	}
}
#endif

/////////////////
//  Operators  //
/////////////////

bool FilterChain::operator==(const FilterChain &other) const
{
	if (filters.size() != other.filters.size())
	{
		return false;
	}

	for (size_t idx = 0; idx < filters.size(); ++idx)
	{
		if (filters[idx] != other.filters[idx])
		{
			return false;
		}
	}

	return true;
}
bool FilterChain::operator!=(const FilterChain &other) const
{
	return !(*this == other);
}

FilterChain& FilterChain::operator+=(const Filter &filterToAdd)
{
	AddFilter(filterToAdd.GetFilterExpression());
	return *this;
}
FilterChain& FilterChain::operator-=(const char *str)
{
	//for (auto filter = filters.begin(); filter != filters.end(); ++filter)
	//{
	//	std::string text = str;
	//	filter->FilterText(text);
	//	if (text != str)
	//	{

	//	}
	//}

	return *this;
}

Filter FilterChain::operator[](int idx) const
{
	return filters[idx];
}
Filter FilterChain::operator[](const char *str) const
{
	for (auto filter = filters.begin(); filter != filters.end(); ++filter)
	{
		std::string text = str;
		filter->FilterText(text);
		if (text != str)
		{
			return *filter;
		}
	}

	return Filter("");
}