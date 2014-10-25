#include "Eq.h"
#include "Utils.h"

#include <sstream>
#include <iostream>
#include <fstream>


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

int EqSolver::Solve(const std::string &equation)
{
	for (auto op : context)
	{
		std::cout << op.token << " " << op.symbol << " " << op.fixity << " " << op.prio << '\n';
	}
	return 0;
}