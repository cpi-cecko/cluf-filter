#pragma once

#include <ctime>
#include <chrono>
#include <random>
#include <functional>


#define SIZE(arr) (sizeof(arr) / sizeof(int))


int* GenerateRandomArray(size_t size)
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

int** AllocateMatrix(size_t rows, size_t cols)
{
	int **matrix = new int*[cols];
	for (size_t col = 0; col < cols; ++col)
	{
		matrix[col] = new int[rows];
	}

	return matrix;
}

void FreeMatrix(int **matrix, size_t cols)
{
	for (size_t col = 0; col < cols; ++col)
	{
		delete [] matrix[col];
	}

	delete [] matrix;
}

int** GenerateRandomMatrix(size_t rows, size_t cols)
{
	std::random_device rd;

	std::default_random_engine e1(rd());
	std::uniform_int_distribution<int> uniform_dist(-40, 40);

	int **matrix = AllocateMatrix(rows, cols);

	for (size_t col = 0; col < cols; ++col)
	{
		for (size_t row = 0; row < rows; ++row)
		{
			matrix[col][row] = uniform_dist(e1);
		}
	}

	return matrix;
}

void PrintMatrix(int **matrix, size_t rows, size_t cols)
{
	for (size_t col = 0; col < cols; ++col)
	{
		for (size_t row = 0; row < rows; ++row)
		{
			std::cout << matrix[col][row] << " ";
		}
		std::cout << '\n';
	}
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
