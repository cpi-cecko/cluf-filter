#ifndef _CLUF__FILTER_H
#define _CLUF__FILTER_H

#include <string>

class Filter
{
private:
	std::string filterExpression; /// @property filterExpression - text which the filter considers as valid

public:
	///
	/// @brief Initializes the Filter instance's filterExpression with newFilterExpression
	///
	Filter(const std::string &newFilterExpression);

	///
	/// @brief Gets the filter expression
	/// @return filterExpression
	///
	std::string GetFilterExpression() const;
	///
	/// @brief Reads the text line by line and checks if filterExpression is represented in it.
	///		   If so, it puts it concatenates it to a filteredText string. In the end, it
	///		   assigns the filteredText to tex
	void FilterText(std::string &text) const;
};

#endif