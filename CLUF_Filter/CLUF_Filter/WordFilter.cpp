#include "WordFilter.h"

#include <string>
#include <fstream>


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

void WordFilter::DoSerialization(std::ofstream &serializationFile) const
{
	serializationFile.write((char*)TYPE_WORD_FILTER, sizeof(FilterType));

	size_t filterExpressionLength = filterExpression.size();
	serializationFile.write((char*)&filterExpressionLength, sizeof(size_t));
	serializationFile.write(filterExpression.c_str(), filterExpressionLength * sizeof(char));
}