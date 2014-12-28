#include "stdafx.h"
#include "XMLReader.h"

#include "XMLDoc.h"

#include <fstream>
#include <algorithm>
#include <functional>
#include <locale>
#include <cctype>
#include <vector>


///////////////////////
// Utility Functions //
///////////////////////
bool IsPostfixOf(const std::string &substr, const std::string &str);
bool IsInfixOf(const std::string &substr, const std::string &str);
void TrimLeft(std::string &line);

bool IsFileNameValid(const std::string &xmlFileName);
// Removes last part of an xmlPath.
// For example, "root/tooth/quux" will be transformed into "root/tooth".
// "root" will be transformed into "".
void RemoveLastPartOfPath(std::string &path);
// Appends a child to the path.
void AppendPath(std::string &path, const std::string &toAppend);
// Extracts a key from a tag.
// <Name> => Name
std::string GetKey(const std::string &tag);
// Extracts all the attribs from a tag.
// <PurchaseOrder PurchaseOrderNumber="99503" OrderDate="1999-10-20">
// => [("PurchaseOrderNumber", "99503"), ("OrderDate", "1999-10-20")]
std::map<std::string, std::string> GetAttribs(const std::string &tag);
// Extracts data from a tag. **Doesn't handle the case where the data may be on a separate line!**
// <City>Mill Valley</City> => Mill Valley
std::string GetData(const std::string &tag);


///////////////////////////
// Reader Implementation //
///////////////////////////
bool XMLReader::ReadInto(XMLDoc *doc, const std::string &inputFile)
{
	if ( ! IsFileNameValid(inputFile))
	{
		return false;
	}


	std::ifstream xmlFile(inputFile);
	if (xmlFile.is_open())
	{
		std::string line;
		std::string accPath = "";
		while (std::getline(xmlFile, line))
		{
			TrimLeft(line);

			if (IsInfixOf("<?", line) || ! IsInfixOf("<", line)) continue;

			if (IsInfixOf("</", line))
			{
				RemoveLastPartOfPath(accPath);
				continue;
			}

			AppendPath(accPath, GetKey(line));

			XMLTag newTag;
			newTag.AddData(GetData(line));
			auto attribs = GetAttribs(line);
			for (auto attrib : attribs)
			{
				newTag.AddAttrib(attrib.first, attrib.second);
			}
			doc->AddTag(accPath, newTag);

			if (line.find("</") != std::string::npos)
			{
				RemoveLastPartOfPath(accPath);
			}
		}

		xmlFile.close();
		return true;
	}
	else return false;
}


const char *xmlExt = ".xml";

bool IsPostfixOf(const std::string &substr, const std::string &str)
{
	size_t substrLen = substr.length();
	if (str.length() > substrLen)
	{
		return str.compare(str.length() - substrLen, substrLen, substr) == 0;
	}
	else return false;
}

bool IsInfixOf(const std::string &substr, const std::string &str)
{
	if (str.length() > substr.length())
	{
		return str.compare(0, substr.length(), substr) == 0;
	}
	else return false;
}

void TrimLeft(std::string &line)
{
	line.erase(line.begin(), 
			   std::find_if(line.begin(), line.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
}

///////////////////////////////////////////////////////////////////////////////

bool IsFileNameValid(const std::string &xmlFileName)
{
	return IsPostfixOf(xmlExt, xmlFileName);
}

void RemoveLastPartOfPath(std::string &path)
{
	if (path.empty())
	{
		return;
	}

	size_t lastSlashPos = path.find_last_of('/');
	if (lastSlashPos != std::string::npos)
	{
		path.erase(lastSlashPos);
	}
	else
	{
		// We're at the parentest parent
		path = "";
	}
}

void AppendPath(std::string &path, const std::string &toAppend)
{
	path += "/";
	path += toAppend;
}

std::string GetKey(const std::string &tag)
{
	std::string result;
	size_t end = tag.find(' ') > tag.find('>') ? tag.find('>') : tag.find(' ');
	result.insert(result.begin(), tag.begin() + 1, tag.begin() + end);
	return result;
}

std::map<std::string, std::string> GetAttribs(const std::string &tag)
{
	size_t beg = tag.find(' ');
	size_t end = tag.find(' ', beg + 1);
	size_t endTwo = tag.find('>');
	if (end > endTwo ||
		end == std::string::npos && beg != std::string::npos)
	{
		end = endTwo;
	}

	std::map<std::string, std::string> attribs;
	if (end < beg) // Found a space in the data.
	{
		return attribs;
	}

	while (end != std::string::npos && beg != std::string::npos)
	{
		size_t eq = tag.find('=', beg+1);
		std::string name(tag.begin() + beg + 1, tag.begin() + eq);
		std::string val(tag.begin() + eq + 2, tag.begin() + end - 1);
		attribs.insert(std::make_pair(name, val));

		beg = tag.find(' ', beg + 1);
		end = tag.find(' ', beg + 1);
		if (end == std::string::npos && beg != std::string::npos)
		{
			end = tag.find('>');
		}
	}
	return attribs;
}

std::string GetData(const std::string &tag)
{
	size_t beg = tag.find('>');
	size_t end = tag.find('<', beg + 1);
	if (beg != std::string::npos && end != std::string::npos)
	{
		std::string result(tag.begin() + beg + 1, tag.begin() + end);
		return result;
	}
	return "";
}