#pragma once


#include "Utils.h"


int** MultiplySimple(int **A, int **B, size_t n)
{
	int **C = AllocateMatrix(n, n);
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < n; ++j)
		{
			C[i][j] = 0;
			for (size_t k = 0; k < n; ++k)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
		}
	}

	return C;
}

void SumMatrices(int **A, int **B, int **C, size_t n)
{
	for (size_t col = 0; col < n; ++col)
	{
		for (size_t row = 0; row < n; ++row)
		{
			C[col][row] = A[col][row] + B[col][row];
		}
	}
}


//
// columns!
// A[0]     -> { 5,  6, 13, 12 }
// A[1]     -> { 3, 10, 15,  4 }
// A[2]     -> { 5,  1, 13,  4 }
// A[3]     -> { 1, 10, 11, 22 }
//
void Partition(int **A, size_t n,
			   int **A11, int **A12, int **A21, int **A22)
{
	// A11[0] = A[0];   A12[0] = &A[0][n];
	// A11[1] = A[1];   A12[1] = &A[1][n];	

	// A21[0] = A[n];   A22[0] = &A[n][n];
	// A21[1] = A[n+1]; A22[1] = &A[n+1][n];
	for (size_t i = 0; i < n; ++i)
	{
		A11[i] = A[i];     A12[i] = &A[i][n];
		A21[i] = A[i + n]; A22[i] = &A[i + n][n];
	}
}

int** Multiply_DivConq(int **A, int **B, size_t n)
{
	int **C = AllocateMatrix(n, n);
	if (n == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
	}
	else
	{
		size_t half = n/2;
		int **A11 = new int*[half], **A12 = new int*[half], **A21 = new int*[half], **A22 = new int*[half];
		Partition(A, half, A11, A12, A21, A22);
		int **B11 = new int*[half], **B12 = new int*[half], **B21 = new int*[half], **B22 = new int*[half];
		Partition(B, half, B11, B12, B21, B22);
		int **C11 = new int*[half], **C12 = new int*[half], **C21 = new int*[half], **C22 = new int*[half];
		Partition(C, half, C11, C12, C21, C22);

		SumMatrices(Multiply_DivConq(A11, B11, half),
					Multiply_DivConq(A12, B21, half), C11, half);
		SumMatrices(Multiply_DivConq(A11, B12, half),
					Multiply_DivConq(A12, B22, half), C12, half);
		SumMatrices(Multiply_DivConq(A21, B11, half),
					Multiply_DivConq(A22, B21, half), C21, half);
		SumMatrices(Multiply_DivConq(A21, B12, half),
					Multiply_DivConq(A22, B22, half), C22, half);
	}

	return C;
}