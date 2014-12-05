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
	
	~TestData()
	{
		delete [] data;
	}
};

template<typename T>
struct Test
{
	char *id;		    // ID of test type; used to print a sensible name
	TestData *allData;
	size_t dataCount;

	~Test()
	{
		delete [] id;
		delete [] allData;
	}
};


template<typename T>
void DoTest(Sorter<T> *sorter, Test *test)
{
	for (size_t idx = 0; idx < manyData.dataCount; ++idx)
	{
		sorter.Sort(manyData.allData[idx].data, manyData.allData[idx].count);
		manyData.allData[idx].result = IsSorted(manyData.allData[idx].data, manyData.allData[idx].count);
		manyData.allData[idx].sortTime = sorter.GetSortTime();
	}
}


#endif