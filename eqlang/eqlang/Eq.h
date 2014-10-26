#include <vector>
#include <stack>
#include <string>


struct Operator
{
	char token;   /// Operator token [a-zA-Z]
	char symbol;  /// Operator symbol [+-/*]
	int prio;     /// Operator priority
	bool fixity;  /// Operator fixity - 1 right, 0 left

	Operator()
		: token('\0'), symbol('\0'), prio(0), fixity(false)
	{
	}
};


///
/// @brief Solver of equations defined in an opearator context
///		   Uses the Shunting Yard algorithm (https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
///
class EqSolver
{
private:
	std::vector<Operator> context; // Defines operators
	std::stack<double> operands;
	std::stack<Operator> operators;

public:
	EqSolver();

	void Init(const std::string &contextFile);
	double Solve(const std::string &equation);

private:
	bool TryParseOperand(const std::string &token, double &operand);
	bool TryParseOperator(const std::string &token, Operator &op);

	double PerformOperation(double left, Operator op, double right);
};