#include "Eq.h"


std::vector<Operator> ParseOperators(const char *opsFile)
{
	std::vector<Operator> result;

	std::ifstream data = std::ifstream(opsFile);
	if (data.is_open())
	{
		Operator newOp;
		while (data.good())
		{
			data >> newOp.token;
			data >> newOp.symbol;
			data >> newOp.prio;
			data >> newOp.fixity;
			result.push_back(newOp);
		}

		data.close();
	}

	return result; 
}


Eq::Eq()
	: op(), left(NULL), right(NULL)
{
}
Eq::Eq(const Operator &newOp, int newOperand)
	: op(newOp), operand(newOperand), left(NULL), right(NULL)
{
}

void Eq::CreateContext(const std::vector<Operator> &ops)
{
}

void Eq::CreateEquation(const std::string &equation)
{
}

void Eq::EvalEq()
{
}
	

void Eq::AddEqLeft(Eq *newLeft)
{
}

void Eq::AddEqRight(Eq *newRight)
{
}