#include <iostream>

#include "Eq.h"
#include "Utils.h"

const char *OPS_FILE = "ops.eq";


int main()
{
	EqSolver newEq;
	newEq.Init(OPS_FILE);

	std::string eq = "31 a ( 5 b 32 f 10 e -210 ) c 324 d 17";
	std::cout << eq << " = " << newEq.Solve(eq) << '\n';

	return 0;
}