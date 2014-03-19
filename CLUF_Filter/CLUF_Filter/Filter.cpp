#include "Filter.h"

#include <string>
#include <iostream>

Filter::Filter(const std::string &fileName)
{
	inputFileStream.open(fileName.c_str());
}
Filter::~Filter()
{
	inputFileStream.close();
}

void Filter::ReadFile()
{
	if (inputFileStream.is_open())
	{
		fileStream << inputFileStream.rdbuf();
	}
	else
	{
		std::printf("Error: File not open");
	}
}

void Filter::OutputFilterWord(const std::string &word)
{
	std::printf("Read string:\n");

	std::string currentLine;
	while (std::getline(fileStream, currentLine))
	{
		if (currentLine.find(word) != std::string::npos)
		{
			std::printf("Line: %s\n", currentLine.c_str());
		}
	}
}