#ifndef TEST_FNS_H
#define TEST_FNS_H


#include "Sorter.h"


template<typename T>
struct TestData
{
	T *data;		// Array of test data
	size_t count;
	unsigned long long sortTime;
	bool result;

	void InitData(const T *newData, size_t newCount);
	
	TestData()
	{
		data = NULL;
		count = 0;
		sortTime = 0;
		result = false;
	}
	~TestData()
	{
		delete [] data;
	}
};

template<typename T>
void TestData<T>::InitData(const T *newData, size_t newCount)
{
	count = newCount;

	if (newData == NULL || count == std::numeric_limits<size_t>::max())
	{
		data = NULL;
		return;
	}

	data = new T[count];
	for (size_t idx = 0; idx < count; ++idx)
	{
		data[idx] = newData[idx];
	}
}


template<typename T>
struct Test
{
	char *sorterId;
	char *id;		    // ID of test type; used to print a sensible name
	TestData<T> *allData;
	size_t dataCount;

	Test()
	{
		sorterId = NULL;
		id = NULL;
		allData = NULL;
		dataCount = 0;
	}

	~Test()
	{
		delete [] allData;
	}
};


template<typename T>
void DoTest(SorterImplementation<T> *sorter, Test<T> *test)
{
	for (size_t idx = 0; idx < test->dataCount; ++idx)
	{
		sorter->Sort(test->allData[idx].data, test->allData[idx].count);
		test->allData[idx].result = IsSorted(test->allData[idx].data, test->allData[idx].count);
		test->allData[idx].sortTime = sorter->GetSortTime();
	}
}

///
/// Checks if an array is sorted by ascending order
///
template<typename T>
bool IsSorted(const T *data, size_t count)
{
	if (data == NULL || count == std::numeric_limits<size_t>::max())
	{
		return true; // For our use-case it is safe to assume that null data is sorted data.
					 // An assertion would just break our tests. In the real world, though, we may use
					 // one or use some kind of logging mechanism.
	}

	for (size_t idx = 0; idx < count-1; ++idx)
	{
		if (data[idx] > data[idx+1])
		{
			return false;
		}
	}
	return true;
}

template<typename T>
void PrintArray(const T *data, size_t count)
{
	if (data == NULL) return;

	std::cout << ArrayToString(data, count);
}

template<typename T>
std::string ArrayToString(const T *data, size_t count)
{
	if (data == NULL) return "";

	std::ostringstream arrStream;

	arrStream << "{ ";
	for (size_t idx = 0; idx < count-1; ++idx)
	{
		arrStream << data[idx] << ", ";
	}
	arrStream << data[count-1];
	arrStream << " }";

	return arrStream.str();
}


#endif