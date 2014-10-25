#include <iostream>

#include "Eq.h"

const char *OPS_FILE = "ops.eq";


int main()
{
	std::vector<Operator> ops = ParseOperators(OPS_FILE);

	Eq newEq;
	newEq.CreateContext(ops);


	std::string eq;
	std::cin >> eq;
	newEq.CreateEquation(eq);
	newEq.EvalEq();

	return 0;
}