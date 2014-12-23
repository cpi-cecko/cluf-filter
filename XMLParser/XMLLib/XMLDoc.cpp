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
}
bool XMLTag::ModifyAttrib(const std::string &attribKey, const std::string &attribVal)
{
	return false;
}

bool XMLTag::DeleteAttrib(const std::string &attribKey)
{
	return false;
}
void XMLTag::DeleteData()
{
}

void XMLTag::AddAttrib(const XMLAttrib &newAttrib)
{
}
void XMLTag::AddData(const XMLData &newData)
{
}

bool XMLTag::HasData() const
{
	return false;
}
bool XMLTag::HasAttribAt(const std::string &key) const
{
	return false;
}

const XMLData& XMLTag::GetData() const
{
	return data;
}
std::vector<XMLAttrib> XMLTag::GetAttribs() const
{
	return attribs;
}
const XMLAttrib& XMLTag::GetAttribWithKey(const std::string &key) const
{
	return attribs[0];
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
bool XMLDoc::AddAttrib(const std::string &pathToTag, const XMLAttrib &newAttrib)
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