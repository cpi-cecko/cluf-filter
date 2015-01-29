#include <iostream>


class Shape
{
public:
	virtual float area() = 0;
	virtual float circ() = 0;
};

class Circle : public Shape
{
public:
	Circle(float newR)
		: r(newR)
	{
	}

	float area()
	{
		return 3.14f * r * r;
	}

	float circ()
	{
		return 2.0f * 3.14f * r;
	}

private:
	float r;
};

class Rect : public Shape
{
public:
	Rect(float newD, float newH)
		: d(newD), h(newH)
	{
	}

	float area()
	{
		return d * h;
	}

	float circ()
	{
		return 2.0f * (d * h);
	}

private:
	float d;
	float h;
};

class Square : public Rect
{
public:
	Square(float newD)
		: Rect(newD, newD) {}
};


int main()
{
	Square sq(3);
	std::cout << sq.area();

	return 0;
}