#ifndef SORTER_H
#define SORTER_H


class Sorter
{
public:
	template<typename T>
	virtual void Sort(T *data, size_t count) = 0;

	virtual unsigned long long GetSortTime() const = 0;
};


#endif