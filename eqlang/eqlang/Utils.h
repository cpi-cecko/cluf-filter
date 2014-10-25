#include <sstream>
#include <vector>


namespace Utils
{
	template <class Src, class Dst>
	bool SafeLexicalCast(const Src &from, Dst &result)
	{
		std::istringstream iss(from);
		iss >> result; 
		if ( ! iss.fail() && iss.eof())
		{
			return true;
		}

		return false;
	}

	std::vector<std::string> Tokenize(const std::string &eq);
}