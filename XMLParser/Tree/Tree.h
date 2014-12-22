#pragma once


#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cctype>


template <class VAL_TYPE>
struct Result;

/*
	`Tree` is an implementation of a key-value map with repeating keys.
	The elements of the map are indexed by an expression defining the path
	to a certain node.

	For example, if we have the following tree:
		/root
		|---/person
			|---/name
				|---"One"
			|---/name
				|---"Something"
		|---/person
			|---/name
				|---"Two"
			|---/email
				|---"example@example.com"

	To get **all** names of **all** people, we'd use:
		tree.At("root/person/names");

	The `/` (forward slash) is the delimiter.

	Valid symbols for keys are [a-zA-Z0-9].

	A key can either begin with `/` (forward slash) or the root key name.
	E.g: Both are equal - "/root/person" or "root/person"
*/
template <class VAL_TYPE>
class Tree
{
public:
	// Inserts a value at a given key.
	// If the key already exists, creates a new key and adds the value to it.
	// If the key contains invalid characters, returns `false`.
	// If the insertion is successful, returns `true`.
	bool Insert(const std::string &atKey, VAL_TYPE newVal);

	// Removes **all** keys which are equal to `atKey`.
	bool Remove(const std::string &atKey);

	// Returns a _Result_ containing `isValid=true` and a 
	// _vector_ of values if there are keys equal to `atKey`
	// Returns a _Result_ containing `isValid=false` if there is
	// no value at `key`.
	Result<VAL_TYPE> At(const std::string &atKey) const;

	bool IsEmpty() const;

public: // public because of UnitTest

	// A valid key only contains ASCII characters [/a-zA-Z0-9] and
	// doesn't have more than one consequentive '/' (forward slash)
	static bool IsKeyValid(const std::string &_key);

	// Separates a key into a current part and a rest part using the forward slash as a
	// delimiter.
	// The current part contains only ASCII chars from [a-zA-Z0-9].
	// The rest part never begins with a '/' (forward slash) and contains the rest of the
	// key or nothing.
	static void ParseKey(const std::string &_key, std::string &current, std::string &rest);

public:
	Tree() 
		: key("/")
	{}

	Tree(const std::string &newKey)
		: key(newKey), isEmpty(true)
	{}

	~Tree()
	{
		for (std::list<Tree*>::iterator child = children.begin();
			 child != children.end(); ++child)
		{
			delete (*child);
		}
		children.clear();
	}


	const std::string &GetKey() const
	{
		return key;
	}

	VAL_TYPE GetVal() const
	{
		return val;
	}

private:
	Tree(const Tree &other);
	Tree &operator=(const Tree &other);

private:
	std::string key;
	VAL_TYPE val;

	std::list<Tree*> children;

	bool isEmpty;
};

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::Insert(const std::string &atKey, VAL_TYPE newVal)
{
	if ( ! IsKeyValid(atKey)) return false;

	std::string _key;
	std::string rest;
	ParseKey(atKey, _key, rest);

	if (key == _key && rest == "")
	{
		val = newVal;
		return true;
	}

	for (std::list<Tree*>::iterator child = children.begin();
		 child != children.end(); ++child)
	{
		if ((*child)->GetKey() == _key)
		{
			(*child)->Insert(rest, newVal);
		}
	}

	isEmpty = false;
	return true;
}

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::Remove(const std::string &atKey)
{
	return false;
}

template <class VAL_TYPE>
Result<VAL_TYPE> Tree<VAL_TYPE>::At(const std::string &atKey) const
{
	Result <VAL_TYPE> result(false);

	result.val.resize(1);

	return result;
}

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::IsEmpty() const
{
	return isEmpty;
}

template <class VAL_TYPE>
void Tree<VAL_TYPE>::ParseKey(const std::string &_key, std::string &current, std::string &rest)
{
	if (_key.empty())
	{
		return;
	}

	size_t begIdx = _key[0] == '/' ? 1 : 0;
	size_t firstSlashPos = _key.find('/', begIdx);

	if (firstSlashPos != std::string::npos)
	{
		current.insert(current.begin(),
					   _key.begin() + begIdx, _key.begin() + firstSlashPos);
		rest.insert(rest.begin(),
					_key.begin() + firstSlashPos + 1, _key.end());

		return;
	}

	current.insert(current.begin(),
				   _key.begin() + begIdx, _key.end());
	rest = "";
}

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::IsKeyValid(const std::string &_key)
{
	bool hasValidCharacters = std::all_of(_key.begin(), _key.end(),
										  [](int i) 
										  {
										      return std::isalnum(i) || i == (int)'/'; 
										  });
	bool hasConsequentiveSlashes = _key.find("//") != std::string::npos;

	return hasValidCharacters && ! hasConsequentiveSlashes;
}


/*
	`Result` is a value which we get after quering the tree for an element.
	To make sure that the element exists, the user should first check `isValid`.
	If `isValid` is `true`, the user can safely query `val`. Otherwise the behavior is
	undefined.
*/
template <class VAL_TYPE>
struct Result
{
	bool isValid;
	std::vector<VAL_TYPE> val;

	Result(bool newIsValid)
		: isValid(newIsValid)
	{
	}
};