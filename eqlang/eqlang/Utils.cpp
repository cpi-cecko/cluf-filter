#include "Utils.h"


std::vector<std::string> Utils::Tokenize(const std::string &eq)
{
	 std::istringstream eqStream(eq);
	 std::string token;
	 std::vector<std::string> result;
	 while (std::getline(eqStream, token, ' '))
	 {
		 result.push_back(token);
	 }
	 return result;
}