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
	return xmlTree.Insert(path, newTag);
}
bool XMLDoc::AddAttrib(const std::string &pathToTag, 
					   const std::string &attribKey, const std::string &attribVal)
{
	// TODO: Tree::At should return a reference to the elements.
	Result<XMLTag*> atKey = xmlTree.At(pathToTag);
	if (atKey.isValid)
	{
		for (XMLTag *val : atKey.val)
		{
			val->AddAttrib(attribKey, attribVal);
		}
		return true;
	}
	return false;
}

bool XMLDoc::ModifyTag(const std::string &path, const XMLTag &modifiedTag)
{
	return xmlTree.Update(path, modifiedTag);
}
bool XMLDoc::ModifyAttrib(const std::string &pathToTag,
				          const std::string &attribKey, const std::string &attribVal)
{
	Result<XMLTag*> atKey = xmlTree.At(pathToTag);
	if (atKey.isValid)
	{
		for (XMLTag *val : atKey.val)
		{
			if ( ! val->ModifyAttrib(attribKey, attribVal))
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool XMLDoc::DeleteTag(const std::string &path)
{
	return xmlTree.Remove(path);
}
bool XMLDoc::DeleteAttrib(const std::string &pathToTag, const std::string &key)
{
	Result<XMLTag*> atKey = xmlTree.At(pathToTag);
	if (atKey.isValid)
	{
		for (XMLTag *val : atKey.val)
		{
			if ( ! val->DeleteAttrib(key))
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}
bool XMLDoc::DeleteDataAtTag(const std::string &pathToTag)
{
	Result<XMLTag*> atKey = xmlTree.At(pathToTag);
	if (atKey.isValid)
	{
		for (XMLTag *val : atKey.val)
		{
			val->DeleteData();
		}
		return true;
	}
	return false;
}

bool XMLDoc::HasDataAt(const std::string &path)
{
	Result<XMLTag*> atKey = xmlTree.At(path);
	return atKey.isValid && atKey.val[0]->HasData();
}
bool XMLDoc::HasAttribAt(const std::string &path, const std::string &key)
{
	Result<XMLTag*> atKey = xmlTree.At(path);
	return atKey.isValid && atKey.val[0]->HasAttribAt(key);
}
bool XMLDoc::HasTagAt(const std::string &path)
{
	return xmlTree.At(path).isValid;
}

std::vector<XMLTag*> XMLDoc::GetTagsAt(const std::string &path)
{
	return xmlTree.At(path).val;
}

TreeIterator<XMLTag> XMLDoc::GetIterator()
{
	return xmlTree.GetBeginIter().Child();
}