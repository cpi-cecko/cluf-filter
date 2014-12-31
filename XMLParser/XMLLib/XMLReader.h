#pragma once


#include <string>
#include <fstream>


class XMLDoc;

// Can't read compact xml :/
class XMLReader
{
public:
	bool ReadInto(XMLDoc *doc, const std::string &inputFile);

private:
	bool ReadIntoH(XMLDoc *doc, std::string &accPath, std::ifstream &xmlFile);
};