#include <fstream>
#include <sstream>

class Filter
{
private:
	std::ifstream inputFileStream;
	std::stringstream fileStream;
	bool isFileRead;

public:
	Filter(const std::string &fileName);
	~Filter();

	void ReadFile();
	void OutputFilterWord(const std::string &word);
};