#ifndef SORTER_H
#define SORTER_H


#include <limits>


template<typename T>
class Sorter
{
public:
	virtual void Sort(T *data, size_t count) = 0;

	virtual unsigned long long GetSortTime() const = 0;
};


template<typename T>
class InsertionSorter : public Sorter<T>
{
public:
	InsertionSorter();

	void Sort(T* data, size_t count);

	unsigned long long GetSortTime() const;
};

template<typename T>
InsertionSorter<T>::InsertionSorter()
{
}

template<typename T>
void InsertionSorter<T>::Sort(T *data, size_t count)
{
	if (data == NULL || count == std::numeric_limits<size_t>::max())
	{
		std::cerr << "Null data in Sort\n";
		return;
	}
}

template<typename T>
unsigned long long InsertionSorter<T>::GetSortTime() const
{
	return 0LL;
}


#endif