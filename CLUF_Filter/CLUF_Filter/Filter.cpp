#include "Filter.h"

#include <sstream>

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
		std::stringstream fileStream;
		fileStream << inputFileStream.rdbuf();
		fileBuffer = fileStream.str();
	}
	else
	{
		std::printf("Error: File not open");
	}
}

void Filter::OutputFilterWord(const std::string &word) const
{
	std::printf("Read string: %s\n", fileBuffer.c_str());
}