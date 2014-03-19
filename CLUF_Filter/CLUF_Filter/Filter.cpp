#include "Filter.h"

#include <string>
#include <iostream>

Filter::Filter(const std::string &fileName)
	: isFileRead(false), fileStream(), inputFileStream(fileName.c_str())
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
		std::printf("Error: File not open\n");
		return;
	}

	fileStream << inputFileStream.rdbuf();
	isFileRead = true;
}

void Filter::OutputFilterWord(const std::string &word)
{
	if (!inputFileStream.is_open())
	{
		std::printf("Error: File not open for filtering\n");
		return;
	}
	if (isFileRead == false)
	{
		std::printf("Warn: File not read\n");
	}

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