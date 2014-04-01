#include "Filter.h"

#include <string>
#include <sstream>
#include <iostream>

Filter::Filter(const std::string &newFilterExpression)
	: filterExpression(newFilterExpression)
{
}

void Filter::FilterText(std::string &text) const
{
	std::string currentLine;
	std::string filteredText;
	std::stringstream streamedText(text);
	while (std::getline(streamedText, currentLine))
	{
		if (currentLine.find(filterExpression) != std::string::npos)
		{
			filteredText.append(currentLine);
			filteredText += "\n";
		}
	}
	text = filteredText;
}

std::string Filter::GetFilterExpression() const
{
	return filterExpression;
}