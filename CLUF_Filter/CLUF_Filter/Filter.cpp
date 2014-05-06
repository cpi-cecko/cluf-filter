#include "Filter.h"

#include <string>
#include <sstream>
#include <iostream>

#include "FilterChain.h"

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

/////////////////
//  Operators  //
/////////////////

Filter& Filter::operator=(const Filter &other)
{
	if (this != &other)
	{
		filterExpression = other.filterExpression;
	}
	return *this;
}

bool Filter::operator==(const Filter &other) const
{
	return filterExpression == other.filterExpression;
}
bool Filter::operator!=(const Filter &other) const
{
	return !(*this == other);
}

std::ostream& Filter::operator<<(std::ostream &os) const
{
	os << filterExpression;
	return os;
}
std::istream& Filter::operator>>(std::istream &is)
{
	is >> filterExpression;
	return is;
}

Filter& Filter::operator+=(char ch)
{
	filterExpression += ch;
	return *this;
}
Filter& Filter::operator+=(const char *str)
{
	filterExpression += str;
	return *this;
}

#ifdef BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
FilterChain operator|(const Filter &lhs, const Filter &rhs)
{
	FilterChain newFilterChain;

	newFilterChain.AddFilter(lhs.GetFilterExpression());
	newFilterChain.AddFilter(rhs.GetFilterExpression());

	return newFilterChain;
}
#endif