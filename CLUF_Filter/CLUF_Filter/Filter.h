#ifndef _CLUF__FILTER_H
#define _CLUF__FILTER_H

#include <sstream>

class Filter
{
private:
	std::string filterExpression;

public:
	Filter(const std::string &newFilterExpression);

	std::string GetFilterExpression() const;
	void FilterStream(std::stringstream &stream) const;
};

#endif