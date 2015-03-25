#include <iostream>
#include <ctime>
#include <chrono>
#include <random>
#include <functional>

#include "MaximumSubarray.h"


#define SIZE(arr) (sizeof(arr) / sizeof(int))


int *GenerateRandomArray(size_t size)
{
	std::random_device rd;

	std::default_random_engine e1(rd());
	std::uniform_int_distribution<int> uniform_dist(-40, 40);

	int *arr = new int[size];

	for (size_t i = 0; i < size; ++i)
	{
		arr[i] = uniform_dist(e1);
	}

	return arr;
}

long long TimeAlgo(std::function<void()> toTest)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	toTest();
	end = std::chrono::system_clock::now();
	std::chrono::milliseconds elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	// std::cout << "Time: " << elapsed_ms.count() << '\n';
	return elapsed_ms.count();
}

void TestWithSamples()
{
	size_t size = 10000;
	const size_t samples = 100;
	long long divTimes[samples];
	long long bruteTimes[samples];

	for (size_t i = 0; i < samples; ++i)
	{
		int *arr = GenerateRandomArray(size);
		divTimes[i] = TimeAlgo(
			[arr, size]() 
			{
				Max found = FindMaxSubarray(arr, 0, size);
				// std::cout << "Divide and Conquer:\n";
				// std::cout << '\t' << found.low << " : " << found.high << " = " << found.sum << '\n';
			});

		bruteTimes[i] = TimeAlgo(
			[arr, size]()
			{
				Max found = Brute_FindMaxSubarray(arr, 0, size);
				// std::cout << "Brute-force:\n";
				// std::cout << '\t' << found.low << " : " << found.high << " = " << found.sum << '\n';
			});
		delete [] arr;
	}

	for (size_t i = 0; i < samples; ++i)
	{
		std::cout << divTimes[i] << " vs. " << bruteTimes[i] << '\n';
	}
}



int main()
{
	size_t size = 10000;

	int *arr = GenerateRandomArray(size);

	Max found = FindMaxSubarray(arr, 0, size);
	std::cout << "Divide and Conquer:\n";
	std::cout << '\t' << found.low << " : " << found.high << " = " << found.sum << '\n';

	found = Brute_FindMaxSubarray(arr, 0, size);
	std::cout << "Brute-force:\n";
	std::cout << '\t' << found.low << " : " << found.high << " = " << found.sum << '\n';

	delete [] arr;

	return 0;
}