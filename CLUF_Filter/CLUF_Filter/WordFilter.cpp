#include "WordFilter.h"

#include <string>


WordFilter::WordFilter(const std::string &newFitlerExpression)
{
	filterExpression = newFitlerExpression;
}

std::string WordFilter::GetFilterExpression() const
{
	return filterExpression;
}

std::string WordFilter::DoFiltering(const std::string &inputText) const
{
	std::string result = "";
	if (inputText.find(filterExpression) != std::string::npos)
	{
		result.append(inputText);
		result += "\n";
	}

	return result;
}