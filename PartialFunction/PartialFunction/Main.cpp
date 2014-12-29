#include <iostream>
#include <functional>


template<class A> 
class optional
{
private:
	bool _isValid;
	A _value;
	
public:
	optional() : _isValid(false) {}
	optional(A v) : _isValid(true), _value(v) {}
	bool isValid() const { return _isValid; }
	A value() const { return _value; }
};

template<class A, class B, class C>
std::function<optional<C>(A)> compose(std::function<optional<B>(A)> m1,
									  std::function<optional<C>(B)> m2)
{
	return [m1, m2](A x) {
		auto b = m1(x);
		if (b.isValid())
		{
			auto c = m2(b.value());
			return c;
		}
		return optional<C>();
	};
}


optional<double> safe_root(double x)
{
	if (x >= 0) return optional<double>(sqrt(x));
	else return optional<double>();
}


int main()
{
	double x = 9;
	auto res = compose<double, double, double>(safe_root, safe_root)(x);
	if (res.isValid())
	{
		std::cout << "Val: " << res.value() << '\n';
	}
	else
	{
		std::cout << "Invalid input\n";
	}

	return 0;
}