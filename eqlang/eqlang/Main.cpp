#include <iostream>

#include "Eq.h"
#include "Utils.h"

const char *OPS_FILE = "ops.eq";


int main()
{
	std::vector<Operator> ops = ParseOperators(OPS_FILE);

	Eq newEq;

	std::string eq = "31 a 5 b 32 f 10 e -210 c 324 d 17";
	std::vector<std::string> tokenizedEq = Utils::Tokenize(eq);
	std::vector<std::string> rest(tokenizedEq.begin() + 2, tokenizedEq.end());
	newEq.ParseEquation(ops, tokenizedEq[0], tokenizedEq[1], rest);
	newEq.EvalEq();

	return 0;
}