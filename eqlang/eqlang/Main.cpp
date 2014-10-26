#include <iostream>

#include "Eq.h"
#include "Utils.h"

const char *OPS_FILE = "ops.eq";


int main()
{
	EqSolver newEq;
	newEq.Init(OPS_FILE);

	std::string eq = "31 a 5 ( b 32 f 10 e -230 ) c 324 d 17";
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