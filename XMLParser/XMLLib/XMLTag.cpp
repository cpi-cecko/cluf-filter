#include "stdafx.h"
#include "XMLTag.h"

#include <assert.h>


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
const std::map<std::string, std::string>& XMLTag::GetAttribs() const
{
	return attribs;
}
#ifdef TEST_BUILD
const std::string& XMLTag::GetAttribWithKey(const std::string &key) const
{
	auto attrib = attribs.find(key);
	assert(attrib != attribs.end());

	return attrib->second;
}
#endif

void XMLTag::Clear()
{
	DeleteData();
	attribs.clear();
}