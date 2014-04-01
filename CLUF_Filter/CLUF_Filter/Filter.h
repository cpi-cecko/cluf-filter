#ifndef _CLUF__FILTER_H
#define _CLUF__FILTER_H

#include <string>

class Filter
{
private:
	std::string filterExpression;

public:
	Filter(const std::string &newFilterExpression);

	std::string GetFilterExpression() const;
	void FilterText(std::string &text) const;
};

#endif