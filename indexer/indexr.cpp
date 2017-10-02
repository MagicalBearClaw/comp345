#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>


std::vector<std::string> getDocuments(const std::string& fileName);

void draw(const std::unordered_map<std::string, int[]>);

int main() {
	std::vector<std::string> docs = getDocuments("index.txt");

	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		std::cout << *it << std::endl;
	}

	return 0;
}

std::vector<std::string> getDocuments(const std::string& fileName)
{

	std::ifstream file(fileName.c_str());
	std::vector<std::string> docs;
	if (!file.is_open())
		std::cout << "Failed to open file: " << fileName << std::endl;
	std::string line;
	while (getline(file, line))
	{
		docs.emplace_back(line);
	}
	return docs;
}

