#pragma once


#include <string>


class XMLDoc;

// Can't read compact xml :/
class XMLReader
{
public:
	bool ReadInto(XMLDoc *doc, const std::string &inputFile);
};