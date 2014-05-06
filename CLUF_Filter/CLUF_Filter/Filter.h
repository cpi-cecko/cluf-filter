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
	///		   If so, it concatenates it to a filteredText string. In the end, it
	///		   assigns the filteredText to text
	///
	void FilterText(std::string &text) const;

public:
	Filter& operator=(const Filter &other);
	bool operator==(const Filter &other) const;
	bool operator!=(const Filter &other) const;

	std::ostream& operator<<(std::ostream &os) const;
	std::istream& operator>>(std::istream &is);

	Filter& operator+=(char ch);
	Filter& operator+=(const char* str);
};

class FilterChain;

///
/// Source of bugs. We may forget to set the filter chain files if we use this to 
/// initialize a brand new FilterChain.
///
/// During the last meeting we decided to drop this operator because it would be a possible source 
/// of hard-to-fix bugs.
///
//FilterChain operator|(const Filter &lhs, const Filter &rhs);


#endif