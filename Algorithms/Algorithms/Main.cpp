#include <iostream>


bool c[5];
void Sum(bool a[], bool b[], size_t n)
{
	bool rem = false;
	size_t i = n-1;
	while (i)
	{
		bool k = a[i] ^ b[i];
		c[i+1] = k ^ rem;
		if ((a[i] == true && rem == true) ||
			(b[i] == true && rem == true) ||
			(a[i] == true && b[i] == true && rem == false))
		{
			rem = true;
		}
		else
		{
			rem = false;
		}
		--i;
	}
	c[0] = rem;

	for (size_t i = 0; i < n+1; ++i)
	{
		std::cout << c[i];
	}
	std::cout << '\n';
}


int main()
{
	bool a[] = { 1, 1, 0, 1 };
	bool b[] = { 1, 0, 1, 1 };
	Sum(a, b, 4);

	return 0;
}