#include <vector>
#include <fstream>
#include <string>


struct Operator
{
	char token;   /// Operator token, such as 'a', 'b', '-', etc.
	char symbol;  /// Operator symbol, such as '+', '-', '*', '/'
	int prio;     /// Operator priority
	bool fixity;  /// Operator fixity - 1 right, 0 left

	Operator()
		: token('\0'), symbol('\0'), prio(0), fixity(false)
	{
	}
};

std::vector<Operator> ParseOperators(const char *opsFile);


class Eq
{
private:
	Eq *left;
	Eq *right;
	Operator op;
	int operand;

public:
	Eq();
	Eq(const Operator &newOp, int newOperand);

	void CreateContext(const std::vector<Operator> &ops);
	void CreateEquation(const std::string &equation);
	void EvalEq();
	
private:
	void AddEqLeft(Eq *newLeft);
	void AddEqRight(Eq *newRight);
};