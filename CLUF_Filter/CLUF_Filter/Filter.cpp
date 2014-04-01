#include "Filter.h"

#include <string>
#include <iostream>

Filter::Filter(const std::string &newFilterExpression)
	: filterExpression(newFilterExpression)
{
}

void Filter::FilterStream(std::stringstream &stream) const
{
	std::string currentLine;
	std::stringstream filteredStream;
	while (std::getline(stream, currentLine))
	{
		if (currentLine.find(filterExpression) != std::string::npos)
		{
			filteredStream << currentLine;
		}
	}
	stream.clear();
	stream << filteredStream;
}

std::string Filter::GetFilterExpression() const
{
	return filterExpression;
}