#include <sstream>
#include <vector>


namespace Utils
{
	// Tries to cast a value from Src to Dst
	// Returns false on failure
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
}