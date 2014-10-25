#include <vector>
#include <fstream>
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

	Eq(const Eq &other);
	Eq& operator=(const Eq &other);
	~Eq();

	void ParseEquation(const std::vector<Operator> &ops, 
					   // (x:y:rest)@equation -- so much funktionality ^_^
					   const std::string &x, const std::string &y, const std::vector<std::string> &rest);
	void EvalEq();
	
private:
	void AddEqLeft(Eq *newLeft);
	void AddEqRight(Eq *newRight);

	void CopyFrom(const Eq &other);
	void Destroy();

	static bool TryGetOperand(const std::string &token, int &newOperand);
	static bool TryGetOperator(const std::vector<Operator> &ops, const std::string &token, Operator &newOp);

	static void CreateOperator(const std::vector<Operator> &ops, Operator &newOperator, char token);
};