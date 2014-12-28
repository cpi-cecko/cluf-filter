#include "stdafx.h"
#include "XMLDoc.h"

#include <assert.h>


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

#ifdef TEST_BUILD
std::vector<XMLTag*> XMLDoc::GetTagsAt(const std::string &path)
{
	auto atPath = xmlTree.At(path);
	assert(atPath.isValid);

	return atPath.val;
}
#endif

TreeIterator<XMLTag> XMLDoc::GetIterator()
{
	assert(xmlTree.GetBeginIter().HasChild());

	return xmlTree.GetBeginIter().Child();
}