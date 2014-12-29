#include <iostream>


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

optional<double> safe_root(double x)
{
	if (x >= 0) return optional<double>(sqrt(x));
	else return optional<double>();
}


int main()
{
	double x = -5;
	auto res = safe_root(x);
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