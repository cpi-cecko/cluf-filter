#ifndef _CLUF__FILTER_H
#define _CLUF__FILTER_H

#include <string>

///
/// @brief Enables dangerous features.
///		   Possible elephant assault on user who uncomments this!
///
#define BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN

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
	///
	/// @brief Standard assignment operator
	///
	Filter& operator=(const Filter &other);
	///
	/// @brief Compares two filters by their filterExpressions
	/// @return true if the filter expressions are equal
	///
	bool operator==(const Filter &other) const;
	///
	/// @brief Compares two filters by their filterExpressions
	/// @return true if the filter expressions are different
	///
	bool operator!=(const Filter &other) const;

	///
	/// @brief Concatenates a character at the end of the filterExpression
	/// @return A Filter with a concatenated character at the end of it
	///
	Filter& operator+=(char ch);
	///
	/// @brief Concatenates a string at the end of the filterExpression
	/// @return A Filter with a concatenated string at the end of it
	///
	Filter& operator+=(const char *str);

public:
	friend std::ostream& operator<<(std::ostream &os, const Filter &filter);
	friend std::istream& operator>>(std::istream &is, Filter &filter);
};

///
/// @brief Write a filterExpression
///
std::ostream& operator<<(std::ostream &os, const Filter &filter);
///
/// @brief Read a filterExpression
///
std::istream& operator>>(std::istream &is, Filter &filter);

///
/// Source of bugs. We may forget to set the filter chain files if we use this to 
/// initialize a brand new FilterChain.
/// Also, this requires the copy constructor to be implemented for FilterChain and set to public. Given
///	that it opens files during its operation, it's better if we prevent its copying and asignment.
///
/// During the last meeting we decided to drop this operator because it would be a possible source 
/// of hard-to-fix bugs.
/// Contact Tsvetan Tsvetanov at cpi.cecko@gmail.com for further info and discussion of the issue.
///
/// OK. If you want to use these things, uncomment #define BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
///
///
/// @brief Creates a new FilterChain with the two Filters as initial filters
/// @return The created filter chain
///
#ifdef BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN
class FilterChain;
FilterChain operator|(const Filter &lhs, const Filter &rhs);
#endif


#endif