#pragma once


#include <vector>


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
template <class KEY_TYPE, class VAL_TYPE>
class Tree
{
public:
	// Inserts a value at a given key.
	// If the key already exists, creates a new key and adds the value to it.
	// If the key contains invalid characters, returns `false`.
	// If the insertion is successful, returns `true`.
	bool Insert(KEY_TYPE key, VAL_TYPE val);
	// Removes **all** keys which are equal to `key`.
	bool Remove(KEY_TYPE key);

	// Returns a _Result_ containing `isValid=true` and a 
	// _vector_ of values if there are keys equal to `key`
	// Returns a _Result_ containing `isValid=false` if there is
	// no value at `key`.
	Result<VAL_TYPE> At(KEY_TYPE key) const;

	bool IsEmpty() const;

private:
};

template <class KEY_TYPE, class VAL_TYPE>
bool Tree<KEY_TYPE, VAL_TYPE>::Insert(KEY_TYPE key, VAL_TYPE val)
{
	return false;
}

template <class KEY_TYPE, class VAL_TYPE>
bool Tree<KEY_TYPE, VAL_TYPE>::Remove(KEY_TYPE key)
{
	return false;
}

template <class KEY_TYPE, class VAL_TYPE>
Result<VAL_TYPE> Tree<KEY_TYPE, VAL_TYPE>::At(KEY_TYPE key) const
{
	return Result<VAL_TYPE>(false);
}

template <class KEY_TYPE, class VAL_TYPE>
bool Tree<KEY_TYPE, VAL_TYPE>::IsEmpty() const
{
	return true;
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