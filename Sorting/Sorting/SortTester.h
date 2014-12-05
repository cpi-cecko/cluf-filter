#ifndef SORT_TESTER_H
#define SORT_TESTER_H


#include "Sorter.h"
#include "TestFns.h"

#include <assert.h>
#include <ostream>


template<typename T>
class SortTester
{
public:
	///
	/// Generates test data and runs sorting tests over each sorting algorithm.
	///
	SortTester(Sorter<T> **sorters, size_t count);

	///
	/// Outputs the test results.
	///
	virtual void GetSummary(std::ostream &out) = 0;

	~SortTester();

private:
	SortTester(const SortTester &other);
	SortTester& operator=(const SortTester &other);

	void GenerateTestData();

private:

	TestData *testsToRun;
	size_t testsCount;
};


template<typename T>
SortTester<T>::SortTester(Sorter<T> **sorters, size_t count)
{
	GenerateTestData();

	assert(testsToRun);

	for (size_t idx = 0; idx < count; ++idx)
	{
		for (size_t testIdx = 0; testIdx < testsCount; ++testIdx)
		{
			testsToRun[testIdx].pTestFn(sorter[idx], testsToRun[testIdx]->allData, testsToRun[testIdx]->dataCount);
		}
	}
}

template<typename T>
void SortTester<T>::GenerateTestData()
{
	testsCount = 4;
	testsToRun = new Test[testsCount];

	testsToRun[0].id = "Test Zero Elements";
	testsToRun[0].dataCount = 2;
	testsToRun[0].allData = new T[testsToRun[0].dataCount];
	testsToRun[0].allData[0].data = NULL;
	testsToRun[0].allData[0].count = 0;
	testsToRun[0].allData[1].data = NULL;
	testsToRun[0].allData[1].count = 13;


}


#endif