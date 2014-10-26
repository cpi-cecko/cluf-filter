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
				
				if (op.token == ')')
				{
					while (lastOp.token != '(')
					{
						double left = operands.top();
						operands.pop();
						double right = operands.top();
						operands.pop();

						double res = PerformOperation(left, lastOp, right);
						operands.push(res);

						operators.pop();
						lastOp = operators.top();

						if (operators.empty())
						{
							std::cerr << "Mismatched brackets\n";
							// TODO: Invalidate equation
							return 0.0;
						}
					}

					assert(operators.top().token == '(');
					operators.pop();
				}

				while ( ! operators.empty() && op.token != '(' &&
						op.prio < lastOp.prio || (op.prio == lastOp.prio && op.fixity == 0))
				{
					lastOp = operators.top();
					double leftOperand = operands.top();
					operands.pop();
					double rightOperand = operands.top();
					operands.pop();

					double res = PerformOperation(leftOperand, lastOp, rightOperand);
					operands.push(res);

					operators.pop();
				}
			}

			if (op.token != ')')
			{
				operators.push(op);
			}
		}
		else
		{
			std::cerr << "Invalid token '" << token << "'\n";
			// TODO: Invalidate equation
			return 0.0;
		}
	}

	while ( ! operators.empty())
	{
		double left = operands.top();
		operands.pop();
		double right = operands.top();
		operands.pop();
		Operator currOp = operators.top();
		operators.pop();

		double res = PerformOperation(left, currOp, right);
		operands.push(res);
	}

	//std::cout << "Operands:\n";
	//while ( ! operands.empty())
	//{
	//	std::cout << operands.top() << '\n';
	//	operands.pop();
	//}
	//std::cout << "Operators:\n";
	//while ( ! operators.empty())
	//{
	//	std::cout << operators.top().token << '\n';
	//	operators.pop();
	//}

	return operands.top();
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

double EqSolver::PerformOperation(double left, Operator op, double right)
{
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
			// TODO: Invalidate operation
			return 0.0;
		}
		return left / right;
	default:
		std::cerr << "Invalid operator\n";
		// TOOD: Invalidate operation
		return 0.0;
	}
}