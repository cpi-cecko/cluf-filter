#include <iostream>
#include <vector>
#include <fstream>
#include <string>

const char *OPS_FILE = "ops.eq";


struct Operator
{
	char token;   /// Operator token, such as 'a', 'b', '-', etc.
	char symbol;  /// Operator symbol, such as '+', '-', '*', '/'
	int prio;     /// Operator priority
	bool fixity;  /// Operator fixity - 1 right, 0 left
};

std::vector<Operator> ParseOperators(const char *opsFile)
{
	std::ifstream data = std::ifstream(opsFile);

	if (data.is_open())
	{
		Operator newOp;
		std::vector<Operator> result;
		while (data.good())
		{
			data >> newOp.token;
			data >> newOp.symbol;
			data >> newOp.prio;
			data >> newOp.fixity;
			result.push_back(newOp);
		}

		data.close();
		return result;
	}
}

int main()
{
	std::vector<Operator> ops = ParseOperators(OPS_FILE);
	for (auto op : ops)
	{
		std::cout << op.token << ' ' << op.symbol << ' ' << op.prio << ' ' << op.fixity << '\n';
	}

	return 0;
}