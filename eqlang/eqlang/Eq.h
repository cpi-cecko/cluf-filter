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
	std::stack<double> operands; // Operand stack
	std::stack<Operator> operators; // Operator stack

	bool isValid; // Flag to to false if there was error while evaluating/parsing the expression
	std::string error; // Error raised during evaluation

public:
	EqSolver();

	void Init(const std::string &contextFile); // Inits operator context
	double Solve(const std::string &equation); // Solves equation based on context

	bool IsValid() const;
	std::string GetError() const;

private:
	bool TryParseOperand(const std::string &token, double &operand) const; // Returns true if the token is an operand
	bool TryParseOperator(const std::string &token, Operator &op) const; // Returns true if the token is an operator

	double PerformCurrentOperation(Operator op); // Pops the last two operands and performs the given op on them
};