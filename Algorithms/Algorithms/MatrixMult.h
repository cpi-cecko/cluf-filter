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
}

void Partition(int **A, int **B,
			   int **A11, int **A12, int **A21, int **A22,
			   int **B11, int **B12, int **B21, int **B22,
			   int **C11, int **C12, int **C21, int **C22)
{
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
		int **A11, **A12, **A21, **A22;
		int **B11, **B12, **B21, **B22;
		int **C11, **C12, **C21, **C22;
		Partition(A, B, 
				  A11, A12, A21, A22,
				  B11, B12, B21, B22,
				  C11, C12, C21, C22);
		SumMatrices(Multiply_DivConq(A11, B11, n/2),
					Multiply_DivConq(A12, B21, n/2), C11, n/2);
		SumMatrices(Multiply_DivConq(A11, B12, n/2),
					Multiply_DivConq(A12, B22, n/2), C12, n/2);
		SumMatrices(Multiply_DivConq(A21, B11, n/2),
					Multiply_DivConq(A22, B21, n/2), C21, n/2);
		SumMatrices(Multiply_DivConq(A21, B12, n/2),
					Multiply_DivConq(A22, B22, n/2), C22, n/2);
	}

	return C;
}