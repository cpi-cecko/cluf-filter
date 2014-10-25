#include "Eq.h"
#include "Utils.h"

#include <sstream>
#include <iostream>


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

Eq::Eq(const Eq &other)
{
	if (this != &other)
	{
		Destroy();
		CopyFrom(other);
	}
}
Eq& Eq::operator=(const Eq &other)
{
	if (this != &other)
	{
		Destroy();
		CopyFrom(other);
	}

	return *this;
}
Eq::~Eq()
{
	Destroy();
}


void Eq::ParseEquation(const std::vector<Operator> &ops,
					   const std::string &x, const std::string &y, const std::vector<std::string> &equation)
{
	if (TryGetOperand(x, operand) && TryGetOperator(ops, y, op))
	{
		// Eq *rightLeaf = new Eq();
		// rightLeaf->ParseEquation(equation[0], equation[1]);
		// AddEqRight(rightLeaf);
	}
	else
	{
		std::cerr << "Invalid token\n";
		// TODO: Invaldate whole operation
		return;
	}
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


bool Eq::TryGetOperand(const std::string &token, int &newOperand)
{
	if (Utils::SafeLexicalCast<std::string, int>(token, newOperand))
	{
		return true;
	}
	return false;
}

bool Eq::TryGetOperator(const std::vector<Operator> &ops, const std::string &token, Operator &newOperator)
{
	if (token.length() == 1 && 
		('a' <= token[0] <= 'z' || 'A' <= token[0] <= 'Z'))
	{
		CreateOperator(ops, newOperator, token[0]);
		return true;
	}
	return false;
}

void Eq::CreateOperator(const std::vector<Operator> &ops, Operator &newOperator, char token)
{
	for (auto opIt = ops.begin(); opIt != ops.end(); ++opIt)
	{
		if (opIt->token == token)
		{
			newOperator.token = token;
			newOperator.symbol = opIt->symbol;
			newOperator.fixity = opIt->fixity;
			newOperator.prio = opIt->prio;
		}
	}
}

void Eq::CopyFrom(const Eq &other)
{
	this->left = other.left;
	this->right = other.right;
	this->op = other.op;
	this->operand = other.operand;
}

void Eq::Destroy()
{
	delete left;
	delete right;
}