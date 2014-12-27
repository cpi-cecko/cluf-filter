#pragma once


#include "../Tree/Tree.h"

#include <map>
#include <string>


#define TEST_BUILD


typedef std::string XMLData;

class XMLTag
{
public:
	XMLTag();

	// Appends `newData` to `data`.
	void ModifyData(const XMLData &dataToAppend);
	// Modifies the attrib corresponding to `attribKey`.
	// If no such attrib is found, returns _false_.
	bool ModifyAttrib(const std::string &attribKey, const std::string &attribVal);

	// Deletes an attrib with the given `attribKey`.
	// If no such attrib is found, returns _false_.
	bool DeleteAttrib(const std::string &attribKey);
	void DeleteData();

	void AddAttrib(const std::string &attribKey, const std::string &attribVal);
	void AddData(const XMLData &newData);

	bool HasData() const;
	bool HasAttribAt(const std::string &key) const;

	const XMLData& GetData() const;
	const std::map<std::string, std::string>& GetAttribs() const;

#ifdef TEST_BUILD
	// Unsafe. Used only for testing.
	const std::string& GetAttribWithKey(const std::string &key) const;
#endif

private:
	std::map<std::string, std::string> attribs;

	XMLData data;
};


class XMLDoc
{
public:
	XMLDoc();

	// Adds `newTag` to the XMLDoc if `path` is a valid path.
	// If the path doesn't exist, it creates a new one.
	bool AddTag(const std::string &path, const XMLTag &newTag);
	// Adds `newAttrib` at all tags corresponding to `pathToTag`.
	// If no such tags are found, returns _false_.
	bool AddAttrib(const std::string &pathToTag, 
				   const std::string &attribKey, const std::string &attribVal);

	// Updates the tags at the given path with the contents of `modifiedTag`.
	// If no such tags are found, returns _false_.
	bool ModifyTag(const std::string &path, const XMLTag &modifiedTag);
	// Updates the attribs in `pathToTag` at `attribKey`.
	// If no such attribs are found, returns _false_.
	bool ModifyAttrib(const std::string &pathToTag,
					  const std::string &attribKey, const std::string &attribVal);

	// Deletes tags at `path`.
	// If no such tags are found, returns _false_.
	bool DeleteTag(const std::string &path);
	// Deletes all attribs at `pathToTag` with a given `key`.
	// If no such attribs are found, returns _false_.
	bool DeleteAttrib(const std::string &pathToTag, const std::string &key);
	// Deletes data at a given tag.
	// Returns _false_ if `path` doesn't exist.
	bool DeleteDataAtTag(const std::string &pathToTag);

	bool HasDataAt(const std::string &path);
	bool HasAttribAt(const std::string &path, const std::string &key);
	bool HasTagAt(const std::string &path);

#ifdef TEST_BUILD
	// Asserts if there ain't tags at this position.
	// The user should check HasTagAt first. Used only for testing.
	std::vector<XMLTag*> GetTagsAt(const std::string &path);
#endif

	TreeIterator<XMLTag> GetIterator();

private:
	Tree<XMLTag> xmlTree;
};