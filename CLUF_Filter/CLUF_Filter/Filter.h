#include <fstream>
#include <sstream>
#include <vector>

class Filter
{
private:
	std::ifstream inputFileStream;
	std::stringstream fileStream;
	std::vector<std::string> filteredFile;
	bool isFileRead;
	bool isFileFiltered;

public:
	Filter(const std::string &fileName);
	~Filter();

	void ReadFile();
	void FilterFile(const std::string &word);

	std::vector<std::string> GetFilteredFile();
};