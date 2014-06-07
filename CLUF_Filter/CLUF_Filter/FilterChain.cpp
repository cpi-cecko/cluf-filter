#include "FilterChain.h"

#include <iostream>
#include <sstream>
#include <algorithm>

FilterChain::FilterChain(const std::string &newInputFileName, const std::string &newOutputFileName)
	: inputFile(newInputFileName), outputFile(newOutputFileName, std::ios::trunc),
	  inputFileName(newInputFileName), outputFileName(newOutputFileName), filters()
{
}
FilterChain::~FilterChain()
{
	inputFile.close();
	outputFile.close();

	for (auto filter = filters.begin(); filter != filters.end(); ++filter)
	{
		delete filter->second;
	}
	filters.clear();
}

void FilterChain::AddFilter(Filter *newFilter, int filterID)
{
	filters.insert(std::make_pair(filterID, newFilter));
}
void FilterChain::RemoveFilter(int filterID)
{
	for (auto filter = filters.begin(); filter != filters.end(); ++filter)
	{
		if (filter->first == filterID)
		{
			filters.erase(filter);
			return;
		}
	}

	std::cerr << "Error: Filter with id `" << filterID << "' not found\n";
}

const std::map<int, Filter*>& FilterChain::GetFilters() const
{
	return filters;
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
			serializationFile.write((char*)&filter->first, sizeof(int));
			filter->second->Serialize(serializationFile);
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
			//size_t filterExpressionLength = 0;
			//serializationFile.read((char*)&filterExpressionLength, sizeof(size_t));
			//char filterExpression[100] = "";
			//serializationFile.read((char*)&filterExpression, filterExpressionLength * sizeof(char));
			//AddFilter(filterExpression);

			// Read filter type. Instantiate new filter. Filter->Deserialize(). Push back to vector.
			FilterType readType;
			serializationFile.read((char*)&readType, sizeof(FilterType));
			switch(readType)
			{
				case TYPE_WORD_FILTER:
					break;
				case TYPE_ENCODE_FILTER:
				case TYPE_DECODE_FILTER:
				case TYPE_ESCAPE_FILTER:
				case TYPE_UNESCAPE_FILTER:
				case TYPE_CAPITALIZE_FILTER:
			}
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
			filter->second->FilterText(filteredText);
		}

		outputFile << filteredText;
		outputFile.flush();
	}
	else
	{
		std::cerr << "Error: Unable to open input or output file.\n";
	}
}

#ifdef BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
void FilterChain::CopyFrom(const FilterChain &other)
{
	if (this != &other)
	{
		inputFileName = other.inputFileName;
		outputFileName = other.outputFileName;
		inputFile.open(inputFileName);
		outputFile.open(outputFileName);
		for (auto filter = other.filters.begin(); filter != other.filters.end(); ++filter)
		{
			AddFilter(filter, filter->first);
		}
	}
}

FilterChain::FilterChain(const FilterChain &other)
{
	CopyFrom(other);
}

FilterChain& FilterChain::operator=(const FilterChain &other)
{
	CopyFrom(other);
	
	return *this;
}
#endif