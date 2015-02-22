#ifndef SORT_TESTER_H
#define SORT_TESTER_H


#include "Sorter.h"
#include "TestFns.h"

#include <assert.h>
#include <ostream>
#include <sstream>


template<typename T>
class SortTester
{
public:
	///
	/// Generates test data and runs sorting tests over each sorting algorithm.
	///
	SortTester(SorterImplementation<T> **sorters, size_t count) {}

	///
	/// Outputs the test results.
	///
	virtual void GetSummary(std::ostream &out) const = 0;

	virtual ~SortTester() {}

private:
	SortTester(const SortTester &other);
	SortTester& operator=(const SortTester &other);
};


template<typename T>
class MySortTester : public SortTester<T>
{
public:
	MySortTester(SorterImplementation<T> **sorters, size_t count);
	~MySortTester();

	void GetSummary(std::ostream &out) const;

private:
	void GenerateTestData();
	void DeleteTests();

private:
	Test<T> *testsToRun;
	size_t testsCount;

	std::stringstream summary;
};

template<typename T>
MySortTester<T>::MySortTester(SorterImplementation<T> **sorters, size_t count) 
	: SortTester<T>(sorters, count)
{
	GenerateTestData();

	assert(testsToRun);

	for (size_t idx = 0; idx < count; ++idx)
	{
		summary << sorters[idx]->GetId() << ":\n";
		for (size_t testIdx = 0; testIdx < testsCount; ++testIdx)
		{
			summary << "  " << testsToRun[testIdx].id << '\n';

			for (size_t dataIdx = 0; dataIdx < testsToRun[testIdx].dataCount; ++dataIdx)
			{
				summary << "	before: ";
				summary << ArrayToString(testsToRun[testIdx].allData[dataIdx].data,
										 testsToRun[testIdx].allData[dataIdx].count);
			}
			summary << '\n';

			DoTest<T>(sorters[idx], &testsToRun[testIdx]);

			for (size_t dataIdx = 0; dataIdx < testsToRun[testIdx].dataCount; ++dataIdx)
			{
				if (testsToRun[testIdx].allData[dataIdx].result)
				{
					summary << "    passed; " << "time " << testsToRun[testIdx].allData[dataIdx].sortTime;
					summary << "; data: ";
					summary << ArrayToString(testsToRun[testIdx].allData[dataIdx].data,
											 testsToRun[testIdx].allData[dataIdx].count);
				}
				else
				{
					summary << "    failed";
				}
				summary << '\n';
			}
		}
		DeleteTests();
		GenerateTestData();
		summary << '\n';
	}
}

template<typename T>
void MySortTester<T>::GetSummary(std::ostream &out) const
{
	out << summary.str();
}

template<typename T>
void MySortTester<T>::DeleteTests()
{
	testsCount = 0;
	delete [] testsToRun;
}

template<typename T>
MySortTester<T>::~MySortTester()
{
	DeleteTests();
}

template<typename T>
void MySortTester<T>::GenerateTestData()
{
	testsCount = 5;
	testsToRun = new Test<T>[testsCount];

	testsToRun[0].id = "Test Zero Elements";
	testsToRun[0].dataCount = 2;
	testsToRun[0].allData = new TestData<T>[testsToRun[0].dataCount];
	testsToRun[0].allData[0].InitData(NULL, 0);
	testsToRun[0].allData[1].InitData(NULL, 13);


	testsToRun[1].id = "Test different arrays";
	testsToRun[1].dataCount = 6;
	testsToRun[1].allData = new TestData<T>[testsToRun[1].dataCount];

	T sorted[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	testsToRun[1].allData[0].InitData(sorted, 9);
	
	T reversed[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	testsToRun[1].allData[1].InitData(reversed, 9);

	T oneTwo[] = {1, 2, 1, 2, 1, 2, 1, 2, 1};
	testsToRun[1].allData[2].InitData(oneTwo, 9);

	T ones[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	testsToRun[1].allData[3].InitData(ones, 9);

	T diff[] = {-1, -5, 0, 4, 15, -15, -3, 4};
	testsToRun[1].allData[4].InitData(diff, 8);

	T halves[] = {1, 2, 3, 4, 5, -1, -2, -3, -4, -5};
	testsToRun[1].allData[5].InitData(halves, 10);


	testsToRun[2].id = "Test negative count";
	testsToRun[2].dataCount = 1;
	testsToRun[2].allData = new TestData<T>[testsToRun[2].dataCount];
	testsToRun[2].allData[0].InitData(NULL, -4);


	testsToRun[3].id = "Test two elements";
	testsToRun[3].dataCount = 3;
	testsToRun[3].allData = new TestData<T>[testsToRun[3].dataCount];
	T two[] = {3, 2};
	testsToRun[3].allData[0].InitData(two, 2);
	T twoSorted[] = {90, 100};
	testsToRun[3].allData[1].InitData(twoSorted, 2);
	T twoEqual[] = {1, 1};
	testsToRun[3].allData[2].InitData(twoEqual, 2);

	testsToRun[4].id = "Big data";
	testsToRun[4].dataCount = 1;
	testsToRun[4].allData = new TestData<T>[testsToRun[4].dataCount];
	T big[] = { 5,3,4,5,6,12,34,0,-1,4,1,2,5,45,623,33,-5,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6666,666,66,6,123,123,123,123,123,
			  -5,-5,-5,-123,55,-3,-5,-6,11,12,13,14,15,16,-533,-1001,101,12,12,12,12,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
			  -12,-16,-66,101,325,14,-5,-6,-7,-8,-9,111,112,113,114,115,116,117,118,119,120,-5,-6,-7,-8,1,2,3,4,5,55,44,33,
			  22,11,0,16,17,18,189,213,76,42,15,-155,10000001,25325,23566,66745,34,467,34,809,9000,101,102,107,22,33,24 };
	testsToRun[4].allData[0].InitData(big, 138);
}


#endif