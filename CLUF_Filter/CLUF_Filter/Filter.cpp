#include "Filter.h"

#include <string>
#include <sstream>
#include <iostream>

#include "FilterChain.h"


void Filter::FilterText(std::string &text) const
{
	std::string currentLine;
	std::string filteredText;
	std::stringstream streamedText(text);
	while (std::getline(streamedText, currentLine))
	{
		//if (currentLine.find(filterExpression) != std::string::npos)
		//{
		//	filteredText.append(currentLine);
		//	filteredText += "\n";
		//}
		std::string resultText = DoFiltering(currentLine);
		filteredText.append(resultText);
	}
	text = filteredText;
}