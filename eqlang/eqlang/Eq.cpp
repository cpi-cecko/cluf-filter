#include "Eq.h"
#include "Utils.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <assert.h>


std::vector<Operator> ParseOperators(const std::string &opsFile)
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


EqSolver::EqSolver()
	: context(0), operands(), operators()
{
}

void EqSolver::Init(const std::string &contextFileName)
{
	context = ParseOperators(contextFileName);
}

double EqSolver::Solve(const std::string &equation)
{
	std::istringstream eqStream(equation);
	std::string token;
	double result = 0.0;
	while (std::getline(eqStream, token, ' '))
	{
		double operand = 0.0;
		Operator op;
		if (TryParseOperand(token, operand))
		{
			operands.push(operand);
		}
		else if (TryParseOperator(token, op))
		{
			operators.push(op);
		}
		else
		{
			std::cerr << "Invalid token '" << token << "'\n";
			// TODO: Invalidate equation
			return 0.0;
		}
	}

	std::cout << "Operands:\n";
	while ( ! operands.empty())
	{
		std::cout << operands.top() << '\n';
		operands.pop();
	}
	std::cout << "Operators:\n";
	while ( ! operators.empty())
	{
		std::cout << operators.top().token << '\n';
		operators.pop();
	}

	return 0.0;
}

bool EqSolver::TryParseOperand(const std::string &token, double &operand)
{
	if (Utils::SafeLexicalCast<std::string, double>(token, operand))
	{
		return true;
	}

	return false;
}

bool EqSolver::TryParseOperator(const std::string &token, Operator &op)
{
	assert (token.size() == 1);

	for (auto opIt = context.begin(); opIt != context.end(); ++opIt)
	{
		if (token[0] == opIt->token)
		{
			op.token = opIt->token;
			op.symbol = opIt->symbol;
			op.prio = opIt->prio;
			op.fixity = opIt->fixity;
			return true;
		}
		else if (token[0] == '(' || token[0] == ')')
		{
			op.token = token[0];
			return true;
		}
	}

	return false;
}