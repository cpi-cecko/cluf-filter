#pragma once


#include <vector>
#include <list>


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

	static void ParseKey(const std::string &_key, std::string &current, std::string &rest);
private:
	static bool IsKeyValid(const std::string &_key);

public:
	Tree() 
		: key("/")
	{}

	Tree(const std::string &newKey)
		: key(newKey)
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

private:
	Tree(const Tree &other);
	Tree &operator=(const Tree &other);

private:
	std::string key;
	VAL_TYPE val;

	std::list<Tree*> children;
};

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::Insert(const std::string &atKey, VAL_TYPE newVal)
{
	std::string _key;
	std::string rest;
	ParseKey(atKey, _key, rest);

	std::string _keyTwo;
	std::string restTwo;
	ParseKey(rest, _keyTwo, restTwo);

	std::string _keyThree;
	std::string restThree;
	ParseKey(restTwo, _keyThree, restThree);

	std::string _keyFour;
	std::string restFour;
	ParseKey(restThree, _keyFour, restFour);

	std::string _keyFive;
	std::string restFive;
	ParseKey(restFour, _keyFive, restFive);

	return false;
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
	return true;
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