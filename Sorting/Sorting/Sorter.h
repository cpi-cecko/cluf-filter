#ifndef SORTER_H
#define SORTER_H


#include <limits>
#include <chrono>


template<typename T>
class Sorter
{
public:
	virtual void Sort(T *data, size_t count) = 0;

	virtual unsigned long long GetSortTime() const = 0;
};


/////////////////////////////////////
// Custom Implementation Interface //
/////////////////////////////////////
template<typename T>
class SorterImplementation
{
public:
	SorterImplementation();

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
SorterImplementation<T>::SorterImplementation()
{
	elapsedTime_micros = std::chrono::microseconds::zero();
}

template<typename T>
void SorterImplementation<T>::Sort(T *data, size_t count)
{
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

	void DoSort(T* data, size_t count);
};

template<typename T>
InsertionSorter<T>::InsertionSorter()
	: SorterImplementation<T>()
{
}

template<typename T>
void InsertionSorter<T>::DoSort(T *data, size_t count)
{
	if (data == NULL || count == std::numeric_limits<size_t>::max())
	{
		std::cerr << "Null data in Insertion Sort\n";
		return;
	}

}


#endif