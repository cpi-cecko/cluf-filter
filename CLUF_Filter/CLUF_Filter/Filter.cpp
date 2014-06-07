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
		std::string resultText = DoFiltering(currentLine);
		filteredText.append(resultText);
	}
	text = filteredText;
}

void Filter::Serialize(std::ofstream &serializationFile) const
{
	DoSerialization(serializationFile);
}