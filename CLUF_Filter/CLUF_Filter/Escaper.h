#ifndef _CLUF_ESCAPER_H
#define _CLUF_ESCAPER_H


class ZeroEscapeFilter : public Filter
{
private:
	virtual std::string DoFiltering(const std::string &inputText) const;
};

class ZeroUnescapeFilter : public Filter
{
private:
	virtual std::string DoFiltering(const std::string &inputText) const;
};


#endif