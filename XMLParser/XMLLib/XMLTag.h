#pragma once


#include <string>
#include <map>


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

	void Clear();

private:
	std::map<std::string, std::string> attribs;

	XMLData data;
};

