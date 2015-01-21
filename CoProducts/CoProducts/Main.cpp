#include <iostream>


template<class L, class R>
class Either
{
	enum 
	{
		isLeft,
		isRight
	} tag;

	union 
	{
		L left;
		R right;
	} val;

public:
	L& Left()
	{
		if (tag != isLeft)
			val.left = L();
		tag = isLeft;
		return val.left;
	}

	R& Right()
	{
		if (tag != isRight)
			val.right = R();
		tag = isRight;
		return val.right;
	}

	R GetRight() const
	{
		return val.right;
	}

	L GetLeft() const
	{
		return val.left;
	}

	bool IsLeft() const
	{
		return tag == isLeft;
	}
};

int m(const Either<int, bool> &e)
{
	if (e.IsLeft())
	{
		return e.GetLeft();
	}
	
	return e.GetRight() ? 0 : 1;
}


int main()
{
	Either<int, bool> isFailure;
	isFailure.Left() = 15;
	isFailure.Right() = true;
	std::cout << m(isFailure) << '\n';

	return 0;
}