#pragma once


#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <cctype>


template <class VAL_TYPE>
struct Result;

template <class VAL_TYPE>
class TreeIterator;

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
	bool Insert(const std::string &atKey, const VAL_TYPE &newVal);

	// Removes **all** keys which are equal to `atKey`.
	bool Remove(const std::string &atKey);

	// Returns a _Result_ containing `isValid=true` and a 
	// _vector_ of values if there are keys equal to `atKey`
	// Returns a _Result_ containing `isValid=false` if there is
	// no value at `key`.
	Result<VAL_TYPE*> At(const std::string &atKey);

	// Updates a value at a specific key
	bool Update(const std::string &atKey, const VAL_TYPE &newVal);

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
		: key("/"), isEmpty(true), hasVal(false),
		  parent(NULL), rightNephew(NULL)
	{}

	Tree(const std::string &newKey)
		: key(newKey), isEmpty(true), hasVal(false),
		  parent(NULL), rightNephew(NULL)
	{}

	Tree(const std::string &newKey, const VAL_TYPE &newVal)
		: key(newKey), val(newVal), isEmpty(false), hasVal(true),
		  parent(NULL), rightNephew(NULL)
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


	const std::string& GetKey() const
	{
		return key;
	}

	bool HasVal() const
	{
		return hasVal;
	}
	VAL_TYPE* GetVal()
	{
		return &val;
	}
	void SetVal(const VAL_TYPE &newVal)
	{
		val = newVal;
		hasVal = true;
	}

	TreeIterator<VAL_TYPE> GetBeginIter();

private:
	Tree(const Tree &other);
	Tree &operator=(const Tree &other);

private:
	std::string key;
	VAL_TYPE val;

	std::list<Tree*> children;
	Tree *parent;
	Tree *rightNephew;

	bool isEmpty;
	bool hasVal;

	friend class TreeIterator<VAL_TYPE>;
};

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::Insert(const std::string &atKey, const VAL_TYPE &newVal)
{
	if ( ! IsKeyValid(atKey)) return false;

	std::string _key;
	std::string rest;
	ParseKey(atKey, _key, rest);

	if (std::find_if(children.begin(), children.end(),
					 [&_key](const Tree *child)
					 {
						 return child->GetKey() == _key;
					 })
		== children.end())
	{
		Tree *newChild;
		if (rest != "")
		{
			newChild = new Tree(_key);
			newChild->Insert(rest, newVal);
		}
		else
		{
			newChild = new Tree(_key, newVal);
		}
		newChild->parent = this;
		if ( ! children.empty())
		{
			children.back()->rightNephew = newChild;
		}
		children.push_back(newChild);

		isEmpty = false;
		return true;
	}

	for (std::list<Tree*>::iterator child = children.begin();
		 child != children.end(); ++child)
	{
		if ((*child)->GetKey() == _key && rest != "")
		{
			(*child)->Insert(rest, newVal);
		}
		else if ((*child)->GetKey() == _key)
		{
			Tree *newChild = new Tree(_key, newVal);
			newChild->parent = this;
			if ( ! children.empty())
			{
				children.back()->rightNephew = newChild;
			}
			children.push_back(newChild);
			break;
		}
	}

	isEmpty = false;
	return true;
}

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::Remove(const std::string &atKey)
{
	if ( ! IsKeyValid(atKey)) return false;

	std::string _key;
	std::string rest;
	ParseKey(atKey, _key, rest);

	// If rest is empty, then try to remove children with keys equal to `_key`.
	if (rest == "")
	{
		std::list<Tree*>::iterator iterRem = std::remove_if(children.begin(), children.end(),
														    [&_key](const Tree *child)
														    {
														        return child->GetKey() == _key;
														    });
		if (iterRem == children.end())
		{
			return false;
		}

		// If we need to delete all children, we shouldn't revalidate their nephews.
		if (iterRem != children.begin())
		{
			// Revalidates nephews.
			for (std::list<Tree*>::iterator alive = children.begin(); alive != --iterRem; ++alive)
			{
				if (alive != children.end())
				{
					(*alive)->rightNephew = (*(++alive));
					--alive;
				}
			}
			++iterRem;
		}

		children.erase(iterRem, children.end());
		isEmpty = children.empty();
		return true;
	}

	// Navigate to the key end
	for (std::list<Tree*>::iterator child = children.begin();
		 child != children.end(); ++child)
	{
		if ((*child)->GetKey() == _key && rest != "")
		{
			return (*child)->Remove(rest);
		}
	}

	return false;
}

template <class VAL_TYPE>
Result<VAL_TYPE*> Tree<VAL_TYPE>::At(const std::string &atKey)
{
	if ( ! IsKeyValid(atKey)) return Result<VAL_TYPE*>(false);

	std::string _key;
	std::string rest;
	ParseKey(atKey, _key, rest);

	Result<VAL_TYPE*> result(false);

	for (std::list<Tree*>::const_iterator child = children.begin();
		 child != children.end(); ++child)
	{
		if ((*child)->GetKey() == _key && rest != "")
		{
			Result<VAL_TYPE*> childRes = (*child)->At(rest);
			if (childRes.isValid)
			{
				result = childRes;
			}
		}
		else if ((*child)->GetKey() == _key)
		{
			result.val.push_back((*child)->GetVal());
			result.isValid = true;
		}
	}

	return result;
}

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::Update(const std::string &atKey, const VAL_TYPE &newVal)
{
	if ( ! IsKeyValid(atKey)) return false;

	std::string _key;
	std::string rest;
	ParseKey(atKey, _key, rest);

	bool result = false;

	for (std::list<Tree*>::iterator child = children.begin();
		 child != children.end(); ++child)
	{
		if ((*child)->GetKey() == _key && rest != "")
		{
			result = (*child)->Update(rest, newVal);
		}
		else if ((*child)->GetKey() == _key)
		{
			(*child)->SetVal(newVal);
			result = true;
		}
	}

	return result;
}

template <class VAL_TYPE>
bool Tree<VAL_TYPE>::IsEmpty() const
{
	return isEmpty;
}

template <class VAL_TYPE>
TreeIterator<VAL_TYPE> Tree<VAL_TYPE>::GetBeginIter()
{
	Tree<VAL_TYPE> *beginNode = parent ? parent : this;
	while (parent && parent->parent)
	{
		beginNode = parent->parent;
	}
	return TreeIterator<VAL_TYPE>(beginNode);
}


///////////////////////
// Utility Functions //
///////////////////////
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
	bool hasOnlyOneSlash = _key.size() == 1 && _key[0] == '/';

	return hasValidCharacters && 
			! hasConsequentiveSlashes &&
			! hasOnlyOneSlash &&
			! _key.empty();
}


/*
	`TreeIterator` is used to provide iterator access to all of the tree's nodes.
*/
template <class VAL_TYPE>
class TreeIterator
{
public:
	// Iterates through siblings
	bool HasNext() const;
	TreeIterator<VAL_TYPE> Next();

	// Iterates through children
	bool HasChild() const;
	TreeIterator<VAL_TYPE> Child();

	// Clears the walked vector
	void Reset();

	Tree<VAL_TYPE>* Deref();

public:
	TreeIterator()
		: currentNode(NULL)
	{
	}

	TreeIterator(Tree<VAL_TYPE> *newCurrentNode)
		: currentNode(newCurrentNode)
	{
	}

private:
	Tree<VAL_TYPE> *currentNode;
	// We shouldn't go through nodes which are already walked.
	std::vector<Tree<VAL_TYPE>*> walked;
};

template <class VAL_TYPE>
TreeIterator<VAL_TYPE> TreeIterator<VAL_TYPE>::Next()
{
	if (currentNode->rightNephew)
	{
		if (std::find(walked.begin(), walked.end(), currentNode->rightNephew) == walked.end())
		{
			walked.push_back(currentNode->rightNephew);
			return TreeIterator<VAL_TYPE>(currentNode->rightNephew);
		}
	}

	return TreeIterator<VAL_TYPE>();
}

template <class VAL_TYPE>
bool TreeIterator<VAL_TYPE>::HasNext() const
{
	return currentNode->rightNephew != NULL && 
		   std::find(walked.begin(), walked.end(), currentNode->rightNephew) == walked.end();
}

template <class VAL_TYPE>
TreeIterator<VAL_TYPE> TreeIterator<VAL_TYPE>::Child()
{
	if ( ! currentNode->children.empty())
	{
		if (std::find(walked.begin(), walked.end(), currentNode->children.front()) == walked.end())
		{
			walked.push_back(currentNode->children.front());
			return TreeIterator<VAL_TYPE>(currentNode->children.front());
		}
	}

	return TreeIterator<VAL_TYPE>();
}

template <class VAL_TYPE>
bool TreeIterator<VAL_TYPE>::HasChild() const
{
	return ! currentNode->children.empty() &&
		   std::find(walked.begin(), walked.end(), currentNode->children.front()) == walked.end();
}

template <class VAL_TYPE>
void TreeIterator<VAL_TYPE>::Reset()
{
	walked.clear();
}

template <class VAL_TYPE>
Tree<VAL_TYPE>* TreeIterator<VAL_TYPE>::Deref()
{
	return currentNode;
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