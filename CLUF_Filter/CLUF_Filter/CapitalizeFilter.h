#ifndef _CLUF_CAPITALIZE_FILTER_H
#define _CLUF_CAPITALIZE_FILTER_H


class CapitalizeFilter : public Filter
{
private:
	virtual std::string DoFiltering(const std::string &inputText) const;
};


#endif