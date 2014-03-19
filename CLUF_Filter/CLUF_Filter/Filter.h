#include <fstream>
#include <string>

class Filter
{
private:
	std::ifstream inputFileStream;
	std::string fileBuffer;

public:
	Filter(const std::string &fileName);
	~Filter();

	void ReadFile();
	void OutputFilterWord(const std::string &word) const;
};