#ifndef _CLUF_WORD_FILTER_H
#define _CLUF_WORD_FILTER_H


#include "Filter.h"


class WordFilter : public Filter
{
private:
	std::string filterExpression; /// @property filterExpression - text which the filter considers as valid

public:
	///
	/// @brief Initializes the filter with `newFilterExpression`
	///
	WordFilter(const std::string &newFilterExpression);

	///
	/// @brief Gets the filter expression
	/// @return filterExpression
	///
	std::string GetFilterExpression() const;

private:
	virtual const std::string &DoFiltering(const std::string &inputText) const;
};


#endif