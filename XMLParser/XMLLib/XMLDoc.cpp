#include "stdafx.h"
#include "XMLDoc.h"


////////////
// XMLTag //
////////////
XMLTag::XMLTag() 
{
}

void XMLTag::ModifyData(const XMLData &dataToAppend)
{
	data.append(dataToAppend);
}
bool XMLTag::ModifyAttrib(const std::string &attribKey, const std::string &attribVal)
{
	auto attrib = attribs.find(attribKey);
	if (attrib != attribs.end())
	{
		attrib->second = attribVal;
		return true;
	}
	return false;
}

bool XMLTag::DeleteAttrib(const std::string &attribKey)
{
	return attribs.erase(attribKey) != 0;
}
void XMLTag::DeleteData()
{
	data = "";
}

void XMLTag::AddAttrib(const std::string &attribKey, const std::string &attribVal)
{
	attribs.insert(std::make_pair(attribKey, attribVal));
}
void XMLTag::AddData(const XMLData &newData)
{
	data = newData;
}

bool XMLTag::HasData() const
{
	return ! data.empty();
}
bool XMLTag::HasAttribAt(const std::string &key) const
{
	return attribs.find(key) != attribs.end();
}

const XMLData& XMLTag::GetData() const
{
	return data;
}
std::map<std::string, std::string> XMLTag::GetAttribs() const
{
	return attribs;
}
std::string XMLTag::GetAttribWithKey(const std::string &key) const
{
	auto attrib = attribs.find(key);
	return attrib->second;
}


////////////
// XMLDoc //
////////////
XMLDoc::XMLDoc()
{
}

bool XMLDoc::AddTag(const std::string &path, const XMLTag &newTag)
{
	return false;
}
bool XMLDoc::AddAttrib(const std::string &pathToTag, 
					   const std::string &attribKey, const std::string &attribVal)
{
	return false;
}

bool XMLDoc::ModifyTag(const std::string &path, const XMLTag &modifiedTag)
{
	return false;
}
bool XMLDoc::ModifyAttrib(const std::string &pathToTag,
				  const std::string &attribKey, const std::string &attribVal)
{
	return false;
}

bool XMLDoc::DeleteTag(const std::string &path)
{
	return false;
}
bool XMLDoc::DeleteAttrib(const std::string &pathToTag, const std::string &key)
{
	return false;
}
bool XMLDoc::DeleteDataAtTag(const std::string &pathToTag)
{
	return false;
}

bool XMLDoc::HasDataAt(const std::string &path) const
{
	return false;
}
bool XMLDoc::HasAttribAt(const std::string &path, const std::string &key) const
{
	return false;
}
bool XMLDoc::HasTagAt(const std::string &path) const
{
	return false;
}

std::vector<XMLTag> XMLDoc::GetTagsAt(const std::string &path) const
{
	return std::vector<XMLTag>();
}