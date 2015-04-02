#include <iostream>


#include "Utils.h"
#include "MatrixMult.h"


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
				// Max found = FindMaxSubarray(arr, 0, size);
				// std::cout << "Divide and Conquer:\n";
				// std::cout << '\t' << found.low << " : " << found.high << " = " << found.sum << '\n';
			});

		bruteTimes[i] = TimeAlgo(
			[arr, size]()
			{
				// Max found = Brute_FindMaxSubarray(arr, 0, size);
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
	size_t rows = 2;
	size_t cols = 2;
	int **A = AllocateMatrix(rows, cols);
	A[0][0] = 1; A[0][1] = 3;
	A[1][0] = 7; A[1][1] = 5;
	int **B = AllocateMatrix(rows, cols);
	B[0][0] = 6; B[0][1] = 8;
	B[1][0] = 4; B[1][1] = 2;

	int **C = MultiplySimple(A, B, rows);

	PrintMatrix(A, rows, cols);
	std::cout << "\n*\n\n";
	PrintMatrix(B, rows, cols);
	std::cout << "\n=\n\n";
	PrintMatrix(C, rows, cols);


	FreeMatrix(A, cols);
	FreeMatrix(B, cols);
	FreeMatrix(C, cols);

	return 0;
}