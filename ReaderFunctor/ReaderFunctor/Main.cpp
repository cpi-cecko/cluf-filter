#include <iostream>
#include <functional>
#include <string>


template<class A, class B, class R>
std::function<B(A)> fmap(std::function<A(R)> f, std::function<B(A)> g)
{
	return g(f);
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
	fmap<bool, std::string, int>(is_pos(5), is_true)();

	return 0;
}