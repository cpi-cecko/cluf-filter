#ifndef _CLUF__FILTER_H
#define _CLUF__FILTER_H

#include <string>

///
/// @brief Enables dangerous features.
///		   Possible elephant assault on user who uncomments this!
///
//#define BRUTAL_ELEPHANTS_ARE_COMING_TO_TOWN

enum FilterType
{
	TYPE_WORD_FILTER,
	TYPE_ENCODE_FILTER,
	TYPE_DECODE_FILTER,
	TYPE_ESCAPE_FILTER,
	TYPE_UNESCAPE_FILTER,
	TYPE_CAPITALIZE_FILTER,
};

class Filter
{
public:
	///
	/// @brief Default constructor
	///
	Filter() {}

	///
	/// @brief Virtual destructor for the base class
	///
	virtual ~Filter() {}

	///
	/// @brief Reads the text line by line. Applies DoFiltering to every line and appends the result to
	///		   `text`.
	///
	void FilterText(std::string &text) const;

	///
	/// @brief Serializes the filter. Adds its type first.
	///
	void Serialize(std::ofstream &serializationFile) const;

	///
	/// @brief Deserializes the filter.
	///
	void Deserialize(const std::ifstream &serializationFile);

protected:
	virtual std::string DoFiltering(const std::string &inputText) const = 0;
	
	virtual void DoSerialization(std::ofstream &serializationFile) const = 0;
};



#endif