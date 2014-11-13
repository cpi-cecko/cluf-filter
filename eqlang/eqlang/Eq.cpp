#include "Eq.h"
#include "Utils.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <assert.h>

const char LEFT_BRACKET = '(';
const char RIGHT_BRACKET = ')';


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
	: context(0), operands(), operators(), isValid(true), error("")
{
}

void EqSolver::Init(const std::string &contextFileName)
{
	context = ParseOperators(contextFileName);
	if (context.empty())
	{
		isValid = false;
		error = "Context not initialized\n";
	}
}

double EqSolver::Solve(const std::string &equation)
{
	if (equation.empty())
	{
		isValid = false;
		error = "Empty equation";
		return 0.0;
	}

	std::istringstream eqStream(equation);
	std::string token;
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
			if ( ! operators.empty())
			{
				Operator lastOp = operators.top();
				
				if (op.token == RIGHT_BRACKET)
				{
					while (lastOp.token != LEFT_BRACKET)
					{
						double res = PerformCurrentOperation(lastOp);
						if ( ! isValid) return 0.0;
						operands.push(res);

						operators.pop();
						if (operators.empty())
						{
							error = "Mismatched brackets\n";
							isValid = false;
							return 0.0;
						}

						lastOp = operators.top();
					}

					assert(operators.top().token == LEFT_BRACKET);
					operators.pop();
				}
				else
				{
					while ( ! operators.empty() && op.token != LEFT_BRACKET && operators.top().token != LEFT_BRACKET &&
							(op.prio < lastOp.prio || (op.prio == lastOp.prio && op.fixity == 0)))
					{
						lastOp = operators.top();
						double res = PerformCurrentOperation(lastOp);
						if ( ! isValid) return 0.0;
						operands.push(res);

						operators.pop();
					}
				}
			}

			if (op.token != RIGHT_BRACKET)
			{
				operators.push(op);
			}
		}
		else
		{
			error = "Invalid token '" + token + "'\n";
			isValid = false;
			return 0.0;
		}
	}

	while ( ! operators.empty())
	{
		Operator currOp = operators.top();
		if (currOp.token == RIGHT_BRACKET)
		{
			error = "Mistmatched brackets\n";
			isValid = false;
			return 0.0;
		}
		operators.pop();

		double res = PerformCurrentOperation(currOp);
		if ( ! isValid) return 0.0;
		operands.push(res);
	}

	return operands.top();
}

bool EqSolver::IsValid() const
{
	return isValid;
}

std::string EqSolver::GetError() const
{
	return error;
}

bool EqSolver::TryParseOperand(const std::string &token, double &operand) const
{
	if (Utils::SafeLexicalCast<std::string, double>(token, operand))
	{
		return true;
	}

	return false;
}

bool EqSolver::TryParseOperator(const std::string &token, Operator &op) const
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
		else if (token[0] == LEFT_BRACKET || token[0] == RIGHT_BRACKET)
		{
			op.token = token[0];
			return true;
		}
	}

	return false;
}

double EqSolver::PerformCurrentOperation(Operator op)
{
	if (operands.empty())
	{
		error = "Missing operand; check equation\n";
		isValid = false;
		return 0.0;
	}
	double right = operands.top();
	operands.pop();
	if (operands.empty())
	{
		error = "Missing operand; check equation\n";
		isValid = false;
		return 0.0;
	}
	double left = operands.top();
	operands.pop();

	switch(op.symbol)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		if (right == 0)
		{
			error = "Division by zero\n";
			isValid = false;
			return 0.0;
		}
		return left / right;
	default:
		error = "Invalid operator\n";
		isValid = false;
		return 0.0;
	}
}