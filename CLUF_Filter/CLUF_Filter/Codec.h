#ifndef _CLUF_CODEC_H
#define _CLUF_CODEC_H


class EncodeFilter : public Filter
{
private:
	virtual const std::string &DoFiltering(const std::string &inputText) const;
};

class DecodeFilter : public Filter
{
private:
	virtual const std::string &DoFiltering(const std::string &inputText) const;
};


#endif