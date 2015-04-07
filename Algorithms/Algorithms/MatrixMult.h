#pragma once


#include "Utils.h"

#include <assert.h>


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

void SubtractMatrices(int **A, int **B, int **C, size_t n)
{
	for (size_t col = 0; col < n; ++col)
	{
		for (size_t row = 0; row < n; ++row)
		{
			C[col][row] = A[col][row] - B[col][row];
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
void Partition(int **A, size_t half,
			   int **A11, int **A12, int **A21, int **A22)
{
	// A11[0] = A[0];   A12[0] = &A[0][n];
	// A11[1] = A[1];   A12[1] = &A[1][n];	

	// A21[0] = A[n];   A22[0] = &A[n][n];
	// A21[1] = A[n+1]; A22[1] = &A[n+1][n];

	// Could be reduced to constant time if we use indexes instead
	// of pointers
	for (size_t i = 0; i < half; ++i)
	{
		A11[i] = A[i];     A12[i] = &A[i][half];
		A21[i] = A[i + half]; A22[i] = &A[i + half][half];
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
		assert (n % 2 == 0); // n must be an exact power of 2

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

		delete [] A11; delete [] B11; delete [] C11;
		delete [] A12; delete [] B12; delete [] C12;
		delete [] A21; delete [] B21; delete [] C21;
		delete [] A22; delete [] B22; delete [] C22;
	}

	return C;
}

int** Multiply_Strassen(int **A, int **B, size_t n)
{
	int **C = AllocateMatrix(n, n);
	if (n == 1)
	{
		C[0][0] = A[0][0] * B[0][0];
	}
	else
	{
		assert (n % 2 == 0); // n must be an exact power of 2

		size_t half = n/2;
		// So much allocations!!!
		int **A11 = new int*[half], **A12 = new int*[half], **A21 = new int*[half], **A22 = new int*[half];
		Partition(A, half, A11, A12, A21, A22);
		int **B11 = new int*[half], **B12 = new int*[half], **B21 = new int*[half], **B22 = new int*[half];
		Partition(B, half, B11, B12, B21, B22);
		int **C11 = new int*[half], **C12 = new int*[half], **C21 = new int*[half], **C22 = new int*[half];
		Partition(C, half, C11, C12, C21, C22);

		int **S1 = AllocateMatrix(half, half); int **S2 = AllocateMatrix(half, half); int **S3 = AllocateMatrix(half, half); int **S4 = AllocateMatrix(half, half); int **S5 = AllocateMatrix(half, half);
		int **S6 = AllocateMatrix(half, half); int **S7 = AllocateMatrix(half, half); int **S8 = AllocateMatrix(half, half); int **S9 = AllocateMatrix(half, half); int **S10 = AllocateMatrix(half, half);

		int **P1 = AllocateMatrix(half, half); int **P2 = AllocateMatrix(half, half); int **P3 = AllocateMatrix(half, half); int **P4 = AllocateMatrix(half, half);
		int **P5 = AllocateMatrix(half, half); int **P6 = AllocateMatrix(half, half); int **P7 = AllocateMatrix(half, half);

		//
		SubtractMatrices(B12, B22, S1, half);
		SumMatrices(A11, A12, S2, half);
		SumMatrices(A21, A22, S3, half);
		SubtractMatrices(B21, B11, S4, half);
		SumMatrices(A11, A22, S5, half);
		SumMatrices(B11, B22, S6, half);
		SubtractMatrices(A12, A22, S7, half);
		SumMatrices(B21, B22, S8, half);
		SubtractMatrices(A11, A21, S9, half);
		SumMatrices(B11, B12, S10, half);

		//
		P1 = Multiply_Strassen(A11, S1, half);
		P2 = Multiply_Strassen(S2, B22, half);
		P3 = Multiply_Strassen(S3, B11, half);
		P4 = Multiply_Strassen(A22, S4, half);
		P5 = Multiply_Strassen(S5, S6, half);
		P6 = Multiply_Strassen(S7, S8, half);
		P7 = Multiply_Strassen(S9, S10, half);

		//
		// C11
		SumMatrices(P5, P4, C11, half);
		SubtractMatrices(C11, P2, C11, half);
		SumMatrices(C11, P6, C11, half);
		// C12
		SumMatrices(P1, P2, C12, half);
		// C21
		SumMatrices(P3, P4, C21, half);
		// C22
		SumMatrices(P5, P1, C22, half);
		SubtractMatrices(C22, P3, C22, half);
		SubtractMatrices(C22, P7, C22, half);


		// delete everythin'
		delete [] A11; delete [] B11; delete [] C11;
		delete [] A12; delete [] B12; delete [] C12;
		delete [] A21; delete [] B21; delete [] C21;
		delete [] A22; delete [] B22; delete [] C22;

		FreeMatrix(S1, half); FreeMatrix(S2, half); FreeMatrix(S3, half); FreeMatrix(S4, half); FreeMatrix(S5, half);
		FreeMatrix(S6, half); FreeMatrix(S7, half); FreeMatrix(S8, half); FreeMatrix(S9, half); FreeMatrix(S10, half);

		FreeMatrix(P1, half); FreeMatrix(P2, half); FreeMatrix(P3, half); FreeMatrix(P4, half);
		FreeMatrix(P5, half); FreeMatrix(P6, half); FreeMatrix(P7, half);
	}

	return C;
}