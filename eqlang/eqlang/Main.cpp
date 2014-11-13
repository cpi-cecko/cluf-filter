#include <iostream>

#include "Eq.h"
#include "Utils.h"


int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: eqlang <context_file> <equation>\n";
		return 0;
	}

	EqSolver newEq;
	newEq.Init(argv[1]);
	if ( ! newEq.IsValid())
	{
		std::cout << newEq.GetError();
		return 0;
	}

	std::string eq = argv[2];
	double result = newEq.Solve(eq);
	
	if (newEq.IsValid())
	{
		std::cout << eq << " = " << result << '\n';
	}
	else
	{
		std::cout << newEq.GetError();
	}

	return 0;
}