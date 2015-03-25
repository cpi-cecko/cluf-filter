#pragma once


size_t DoCount(int *arr, int *arrLeft, size_t leftSize, int *arrRight, size_t rightSize)
{
	size_t idx = 0;
	size_t idxLeft = 0;
	size_t idxRight = 0;

	size_t count = 0;

	while (idxLeft < leftSize && idxRight < rightSize)
	{
		idx++;
		if (arrLeft[idxLeft] > arrRight[idxRight])
		{
			++idxRight;
			++count;
		}
		else
		{
			++idxLeft;
		}
	}

	while (idxLeft < leftSize)
	{
		idx++;
		idxLeft++;
		count++;
	}

	while (idxRight < rightSize)
	{
		idx++;
		idxRight++;
	}

	return count;
}

size_t CountInversionsHelper(int *arr, size_t size, int *buffer)
{
	if (size <= 1)
		return 0;

	size_t count = 0;
	size_t mid = size / 2;
	count += CountInversionsHelper(arr, mid, buffer);
	count += CountInversionsHelper(arr + mid, size - mid, buffer + mid);
	count += DoCount(buffer, arr, mid, arr + mid, size - mid);

	return count;
}

size_t CountInversions(int *arr, size_t size)
{
	if (size == 0)
		return 0;

	int *buffer = new int[size];

	size_t count = CountInversionsHelper(arr, size, buffer);

	delete [] buffer;

	return count;
}
