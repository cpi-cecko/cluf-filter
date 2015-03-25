#pragma once


const int CROSSOVER = 100;

struct Max
{
	size_t low;
	size_t high;
	int sum;

	Max(size_t newLow, size_t newHigh, int newSum)
		: low(newLow), high(newHigh), sum(newSum)
	{
	}

	bool operator>=(const Max &other)
	{
		return sum >= other.sum;
	}
};


Max FindMaxCrossingSubarray(int *arr, size_t low, size_t mid, size_t high)
{
	int leftSum = -9999;
	int sum = 0;
	size_t maxLeft = 0;
	for (int i = mid; i >= int(low); --i)
	{
		sum += arr[i];
		if (sum > leftSum)
		{
			leftSum = sum;
			maxLeft = i;
		}
	}
	int rightSum = -9999;
	sum = 0;
	size_t maxRight = 0;
	for (size_t i = mid+1; i <= high; ++i)
	{
		sum += arr[i];
		if (sum > rightSum)
		{
			rightSum = sum;
			maxRight = i;
		}
	}

	return Max(maxLeft, maxRight, leftSum + rightSum);
}

Max Brute_FindMaxSubarray(int *arr, size_t low, size_t high)
{
	int maxSum = -99999;
	int sum = 0;
	size_t maxLow = 0;
	size_t maxHigh = 0;
	for (size_t i = low; i < high; ++i)
	{
		for (size_t j = i; j < high; ++j)
		{
			sum += arr[j];
			if (sum > maxSum)
			{
				maxSum = sum;
				maxLow = i;
				maxHigh = j;
			}
		}
		sum = 0;
	}

	return Max(maxLow, maxHigh, maxSum);
}

Max FindMaxSubarray(int *arr, size_t low, size_t high)
{
	if (low == high)
	{
		return Max(low, high, arr[low]);
	}
	else
	{
		size_t mid = (high + low) / 2;
		Max leftMax = FindMaxSubarray(arr, low, mid);
		Max rightMax = FindMaxSubarray(arr, mid+1, high);
		Max centerMax = FindMaxCrossingSubarray(arr, low, mid, high);
		if (leftMax >= rightMax && leftMax >= centerMax)
			return leftMax;
		else if (rightMax >= leftMax && rightMax >= centerMax)
			return rightMax;
		else
			return centerMax;
	}
}

Max FindMaxSubarray_Crossover(int *arr, size_t low, size_t high)
{
	if (low == high)
	{
		return Max(low, high, arr[low]);
	}
	else
	{
		if (high <= CROSSOVER)
		{
			return Brute_FindMaxSubarray(arr, low, high);
		}
		else
		{
			size_t mid = (high + low) / 2;
			Max leftMax = FindMaxSubarray(arr, low, mid);
			Max rightMax = FindMaxSubarray(arr, mid+1, high);
			Max centerMax = FindMaxCrossingSubarray(arr, low, mid, high);
			if (leftMax >= rightMax && leftMax >= centerMax)
				return leftMax;
			else if (rightMax >= leftMax && rightMax >= centerMax)
				return rightMax;
			else
				return centerMax;
		}
	}
}