#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <locale>
#include <algorithm>

static int maxWordLength = 0;

std::vector<std::string> getDocuments(const std::string& fileName);
void calculateDocs(const std::vector<std::string>& docs, std::unordered_map<std::string, std::vector<int>>& processedWords);
std::unordered_map<std::string, std::vector<int>> processDocuments(const std::vector<std::string>& docs);
std::unordered_map<std::string, std::vector<int>> buildDictionary(const std::vector<std::string>& docs);

std::vector<std::pair<std::string, std::vector<int>>> mapToVector(std::unordered_map<std::string, std::vector<int>> words);

void draw(const std::unordered_map<std::string, std::vector<int>>& indexed, const int maxWordLength, const std::vector<std::string>& docs);

int main() {
	std::vector<std::string> docs = getDocuments("index.txt");

	std::unordered_map<std::string, std::vector<int>> indexed = processDocuments(docs);
	draw(indexed, maxWordLength, docs);
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

std::unordered_map<std::string, std::vector<int>> processDocuments(const std::vector<std::string>& docs)
{
	/// get all file contents
	std::vector<std::string> readDocs;
	std::stringstream buffer;
	std::unordered_map<std::string, std::vector<int>> processedWords;
	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		std::ifstream file(*it);
		if (!file.is_open())
			std::cout << "Failed to open file: " << *it << std::endl;
		std::stringstream buffer;
		buffer << file.rdbuf();
		readDocs.emplace_back(buffer.str());
		buffer.clear();
	}
	buffer.clear();
	processedWords = buildDictionary(readDocs);
	calculateDocs(readDocs, processedWords);
	return processedWords;
}

std::unordered_map<std::string, std::vector<int>> buildDictionary(const std::vector<std::string>& docs)
{
	size_t current;
	std::string delimiters = " ,-':!().?\";—~{}/*";
	size_t next = -1;
	std::unordered_map<std::string, std::vector<int>> dictionary;
	std::vector<int> defaultcounts;
	defaultcounts.reserve(docs.size());
	defaultcounts.assign(docs.size(), 0);
	std::vector<std::string> words;
	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		do
		{
			current = next + 1;
			std::string doc = *it;
			next = doc.find_first_of(delimiters, current);
			std::string currentword = doc.substr(current, next - current);
			std::transform(currentword.begin(), currentword.end(), currentword.begin(), tolower);
			if (currentword.size() > maxWordLength)
				maxWordLength = currentword.size();

			words.emplace_back(currentword);

		} while (next != std::string::npos);
	}

	std::sort(words.begin(), words.end());
	
	for (std::vector<std::string>::const_iterator it = words.begin(); it != words.end(); ++it)
	{
		if(*it != "")
			dictionary[*it] = defaultcounts;
	}

	return dictionary;
}

void calculateDocs(const std::vector<std::string>& docs, std::unordered_map<std::string, std::vector<int>>& processedWords)
{
	size_t current;
	std::string delimiters = " ,-':!().?\";—~{}/*";
	size_t next = -1;
	int index = 0;
	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		do
		{
			current = next + 1;
			std::string doc = *it;
			next = doc.find_first_of(delimiters, current);
			std::string currentword = doc.substr(current, next - current);
			std::transform(currentword.begin(), currentword.end(), currentword.begin(), tolower);
			if (currentword != "")
			{
				std::vector<int> counts = processedWords[currentword];
				counts[index] = counts[index] + 1;
				processedWords[currentword] = counts;
			}
		} while (next != std::string::npos);
		++index;
	}
}

void draw(const std::unordered_map<std::string, std::vector<int>>& , const int maxWordLength, const std::vector<std::string>& docs)
{
	int horizontalLIne = maxWordLength;

	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		horizontalLIne += docs.size() + 2;
	}

	for (int i = 0; i <= horizontalLIne + 2; i++)
		std::cout << "*";
	std::cout << std::endl;

	for (int i = 0; i <= horizontalLIne + 2; i++)
		std::cout << "*";
	std::cout << std::endl;
}



