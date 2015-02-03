#include <iostream>
#include <functional>
#include <string>


template<class C, class A, class B>
std::function<C(A)> fmap(std::function<B(A)> f, std::function<C(B)> g)
{
	return [f,g](A x) { return g(f(x)); };
}

bool is_pos(int a)
{
	return a > 0;
}

std::string is_true(bool b)
{
	return b == true ? "true" : "false";
}


int main()
{
	std::cout << fmap<std::string, int, bool>(is_pos, is_true)(0) << '\n';

	return 0;
}