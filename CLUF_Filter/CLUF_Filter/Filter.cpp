#include "Filter.h"

#include <string>
#include <iostream>

Filter::Filter(const std::string &fileName)
	: isFileRead(false), isFileFiltered(false), filteredFile(), fileStream(), inputFileStream(fileName.c_str())
{
}
Filter::~Filter()
{
	inputFileStream.close();
}

void Filter::ReadFile()
{
	if (!inputFileStream.is_open())
	{
		std::cerr << "Error: File not open\n";
		return;
	}

	fileStream << inputFileStream.rdbuf();
	isFileRead = true;
}

void Filter::FilterFile(const std::string &word)
{
	if (!inputFileStream.is_open())
	{
		std::cerr << "Error: File not open for filtering\n";
		return;
	}
	if (isFileRead == false)
	{
		std::cerr << "Warn: File not read\n";
	}

	std::string currentLine;
	while (std::getline(fileStream, currentLine))
	{
		if (currentLine.find(word) != std::string::npos)
		{
			filteredFile.push_back(currentLine);
		}
	}
	isFileFiltered = true;
}

std::vector<std::string> Filter::GetFilteredFile()
{
	return filteredFile;
}