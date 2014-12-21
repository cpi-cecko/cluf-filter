#pragma once


#include <vector>


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

template <class KEY_TYPE, class VAL_TYPE>
class Tree
{
public:
	bool Insert(KEY_TYPE key, VAL_TYPE val);
	bool Remove(KEY_TYPE key);

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