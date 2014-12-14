#ifndef SORTER_H
#define SORTER_H


#include <chrono>
#include <string>
#include <assert.h>


template<typename T>
class Sorter
{
public:
	virtual void Sort(T *data, size_t count) = 0;

	virtual unsigned long long GetSortTime() const = 0;

public:
	Sorter(const std::string &newId)
		: id(newId) 
	{}

protected:
	std::string id;

	static void swapless(T &fst, T &snd);
};

template<typename T>
void Sorter<T>::swapless(T &fst, T &snd)
{
	if (fst > snd)
	{
		std::swap(fst, snd);
	}
}


/////////////////////////////////////
// Custom Implementation Interface //
/////////////////////////////////////
template<typename T>
class SorterImplementation : public Sorter<T>
{
public:
	SorterImplementation(const std::string &newId);

	void Sort(T *data, size_t count);
	unsigned long long GetSortTime() const;

protected:
	virtual void DoSort(T *data, size_t count) = 0;

private:
	std::chrono::microseconds elapsedTime_micros;
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;

	void StartTrack();
	void EndTrack();
};

template<typename T>
SorterImplementation<T>::SorterImplementation(const std::string &newId)
	: Sorter(newId)
{
	elapsedTime_micros = std::chrono::microseconds::zero();
}

template<typename T>
void SorterImplementation<T>::Sort(T *data, size_t count)
{
	if (data == NULL)
	{
		return;
	}

	StartTrack();

	DoSort(data, count);

	EndTrack();
}

template<typename T>
void SorterImplementation<T>::StartTrack()
{
	start = std::chrono::steady_clock::now();
}

template<typename T>
void SorterImplementation<T>::EndTrack()
{
	end = std::chrono::steady_clock::now();
	elapsedTime_micros = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
}

template<typename T>
unsigned long long SorterImplementation<T>::GetSortTime() const
{
	return elapsedTime_micros.count();
}


//////////////////////
// Insertion Sorter //
//////////////////////
template<typename T>
class InsertionSorter : public SorterImplementation<T>
{
public:
	InsertionSorter();

	void DoSort(T *data, size_t count);
};

template<typename T>
InsertionSorter<T>::InsertionSorter()
	: SorterImplementation<T>("Insertion Sort")
{
}

template<typename T>
void InsertionSorter<T>::DoSort(T *data, size_t count)
{
	for (size_t i = 1; i < count; ++i)
	{
		size_t j = i;
		while (j > 0 && 
			   data[j-1] > data[j])
		{
			std::swap(data[j-1], data[j]);
			--j;
		}
	}
}


//////////////////
// Quick Sorter //
//////////////////
template<typename T>
class QuickSorter : public SorterImplementation<T>
{
public:
	QuickSorter();

	void DoSort(T *data, size_t count);

private:
	size_t Partition(T *data, size_t count);
};

template<typename T>
QuickSorter<T>::QuickSorter()
	: SorterImplementation("Quick Sort")
{
}

template<typename T>
void QuickSorter<T>::DoSort(T *data, size_t count)
{
	if (count <= 1 || !data)
		return;

	size_t pivotIdx = Partition(data, count);

	DoSort(data, pivotIdx);
	DoSort(data + pivotIdx + 1, count - pivotIdx - 1);
}

template<typename T>
size_t QuickSorter<T>::Partition(T *data, size_t count)
{
	assert (count >= 2);

	if (count == 2)
	{
		swapless(data[0], data[1]);
		return 1;
	}

	size_t middle = count / 2;
	swapless(data[0], data[middle]);
	swapless(data[0], data[count - 1]);
	swapless(data[middle], data[count - 1]);

	std::swap(data[middle], data[count - 2]);
	T &partitioningElem = data[count - 2];

	size_t left = 0;
	size_t right = count - 2;

	while (true)
	{
		while (data[++left] < partitioningElem)
			;

		while (data[--right] > partitioningElem)
		{
			if (right == left)
				break;
		}

		if (left >= right)
			break;

		std::swap(data[left], data[right]);
	}

	std::swap(data[left], partitioningElem);

	return left;
}


#endif