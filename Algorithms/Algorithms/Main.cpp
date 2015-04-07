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
	size_t rows = 64;
	size_t cols = 64;
	int **A = GenerateRandomMatrix(rows, cols);
	int **B = GenerateRandomMatrix(rows, cols);

	int **Cs = MultiplySimple(A, B, rows);
	std::cout << "Multiply Simple:\n";
	PrintMatrix(Cs, rows, cols);

	int **Cdq = Multiply_DivConq(A, B, rows);
	std::cout << "Multiply Divide & Conquer:\n";
	PrintMatrix(Cdq, rows, cols);

	int **Cstr = Multiply_Strassen(A, B, rows);
	std::cout << "Multiply Strassen:\n";
	PrintMatrix(Cstr, rows, cols);

	FreeMatrix(A, cols);
	FreeMatrix(B, cols);
	FreeMatrix(Cs, cols);
	FreeMatrix(Cdq, cols);
	FreeMatrix(Cstr, cols);

	return 0;
}