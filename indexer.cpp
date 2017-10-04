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
#include <iomanip>

/**
 * Assignment 1 - COMP345 - Advanced Programming with c++
 * @author	Michael McMahon		Student ID: 26250912
 * @author	Christopher Dufort	Student ID: 40030286
 * @author	Jesse Tremblay		Student ID: 40027271
 * @version	Assignment1
 * @since	October, 3rd, 2017
 *
 */

//static global variables
static const std::string title = "Dictionary";
static int maxColumnLength = 0;
static int maxWordLength = title.length();
static std::string delimiters = " ,\t-':!().?\";–~{}/*\n\t\r";

static std::vector<std::string> stopWords;

//function declarations
std::vector<std::string> getDocuments(const std::string& fileName);
std::unordered_map<std::string, std::vector<int>> processDocuments(const std::vector<std::string>& docs);
std::unordered_map<std::string, std::vector<int>> buildDictionary(const std::vector<std::string>& docs);
void draw(const std::unordered_map<std::string, std::vector<int>>& indexed, std::vector<std::string> keys, const std::vector<std::string>& docs);
void drawLine(const int length);
void removeStopWords(std::unordered_map<std::string, std::vector<int>>& words, std::string fileName);
std::vector<std::string> mapToVector(std::unordered_map<std::string, std::vector<int>>& words);
std::vector<int> calculatTotalWordCounts(const std::unordered_map<std::string, std::vector<int>>& words, const int numOfDocs);

// function defenitions
/**
* This is the starting point of the program.
*
*/
int main() {
	std::vector<std::string> docs = getDocuments("index.txt");
	if (docs.empty())
	{
		std::cout << "No files to process." << std::endl;
		std::exit(0);
	}

	std::unordered_map<std::string, std::vector<int>> indexed = processDocuments(docs);
	std::vector<std::string> sorted = mapToVector(indexed);
	draw(indexed, sorted, docs);
	removeStopWords(indexed, "stopWords.txt");
	sorted = mapToVector(indexed);
	std::cout << std::endl << "Without stopWords" << std::endl << std::endl;
	draw(indexed, sorted, docs);
	return 0;
}

/**
* This function is responsible for building the vector of string file names.
* @param fileName	The filename of the document to have its contents retrieved
* @return	std::vector<std::string> ...
*/
std::vector<std::string> getDocuments(const std::string& fileName)
{

	std::ifstream file(fileName.c_str());
	std::vector<std::string> docs;

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << fileName << std::endl;
		std::exit(-1);
	}
	std::string line;
	while (getline(file, line))
	{
		if(line != "")
			docs.emplace_back(line);
	}
	return docs;
}

/**
* This function is responsible for building an undordermap conaining words and their associated word counts.
* @param docs	A vector of string which contain various filenames to iterate through
* @return	An unordered_map of type <string,vector<int>> containing all the words and instance counts per file
*/
std::unordered_map<std::string, std::vector<int>> processDocuments(const std::vector<std::string>& docs)
{
	//get all file contents
	std::vector<std::string> readDocs;
	std::stringstream buffer;
	std::unordered_map<std::string, std::vector<int>> processedWords;
	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		if (it->length() > maxColumnLength) {
			maxColumnLength = it->length();
		}
		std::ifstream file(*it);
		if (!file.is_open())
		{
			std::cout << "Failed to open file: " << *it << std::endl;
			std::exit(-1);
		}
		std::stringstream buffer;
		buffer << file.rdbuf();
		readDocs.emplace_back(buffer.str());
		buffer.clear();
	}
	buffer.clear();
	processedWords = buildDictionary(readDocs);
	//calculateDocs(readDocs, processedWords);
	return processedWords;
}

/**
* This function is responsible for building an undordermap conaining words and their associated word counts.
* @param docs	A vector of string which contain various filenames to iterate through
* @return	An unordered_map of type <string,vector<int>> containing all the words and instance counts per file
*/
std::unordered_map<std::string, std::vector<int>> buildDictionary(const std::vector<std::string>& docs)
{
	size_t current;
	size_t next = -1;
	std::unordered_map<std::string, std::vector<int>> dictionary;
	std::vector<int> defaultcounts;
	defaultcounts.reserve(docs.size());
	defaultcounts.assign(docs.size(), 0);
	int docIndex = 0;
	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		do
		{
			current = next + 1;
			std::string doc = *it;
			next = doc.find_first_of(delimiters, current);
			std::string currentword = doc.substr(current, next - current);
			std::transform(currentword.begin(), currentword.end(), currentword.begin(), tolower);
			if (currentword.size() > maxWordLength) {
				maxWordLength = currentword.size();
			}

			if (currentword == "")
				continue;
			std::vector<int> counts = dictionary[currentword];
			if (counts.capacity() == 0)
				counts = defaultcounts;
			counts[docIndex] = counts[docIndex] + 1;
			dictionary[currentword] = counts;
		} while (next != std::string::npos);

		++docIndex;
	}

	return dictionary;
}

/**
* This function is responsible for drawing a table of each words and the count in each document.
* @param words The hashmap of words and their counts
* @param keys	The sorted keys of the hash map;
* @param docs	A vector of string which contain various filenames to iterate through
* 
*/
void draw(const std::unordered_map<std::string, std::vector<int>>& words, std::vector<std::string> keys, const std::vector<std::string>& docs)
{

	int columnCount = docs.size();
	int horizontalLine = (columnCount * (maxColumnLength + 2)) + (maxWordLength + 2) + columnCount + 2;

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	//display a header line including the word dictionary and the list of document names
	std::cout << "* " << std::setw(maxWordLength) << std::left << title;

	//Loop to display all file names seperated by an asterisk
	for (std::vector<std::string>::const_iterator it = docs.begin(); it != docs.end(); ++it)
	{
		std::cout  << " * " << std::setw(maxColumnLength) << std::right << *it;
	}
	std::cout << " *" << std::endl;
	
	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	//main table display
	for (auto it = keys.begin(); it != keys.end(); ++it)
	{
		std::string currentWord = *it;
		std::cout << "* " << std::left << std::setw(maxWordLength) << currentWord;
		std::vector<int> counts = words.at(currentWord);
		for (auto it = counts.begin(); it != counts.end(); ++it)
		{
			std::cout << " * " << std::right << std::setw(maxColumnLength) << *it;
		}
		std::cout << " *" << std::endl;
	}

	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);

	// Display totals
	std::vector<int> totals = calculatTotalWordCounts(words, docs.size());
	std::cout << "* " << std::left << std::setw(maxWordLength) << "total";
	for (auto it = totals.begin(); it != totals.end(); ++it)
	{
		std::cout << " * " << std::right << std::setw(maxColumnLength) << *it;
	}
	std::cout << " *" << std::endl;
	//display a hoirzontal line of asterisks
	drawLine(horizontalLine);
}

/**
 * This function draws a line of asterisks based on provided length paramater.
 * @param length	The length of the line you wish to draw.
 *
 */
void drawLine(const int length) {
	for (int i = 0; i != length; ++i)
		std::cout << "*";
	std::cout << std::endl;
}


std::vector<int> calculatTotalWordCounts(const std::unordered_map<std::string, std::vector<int>>& words, const int numOfDocs)
{
	std::vector<int> totals;
	totals.reserve(numOfDocs);
	totals.assign(numOfDocs, 0);

	for (auto it = words.begin(); it != words.end(); ++it)
	{
		for (int i = 0; i < totals.size(); i++)
		{
			totals[i] += it->second[i];
		}
	}

	return totals;
}

/**
* This function is called to alter the words map to remove all isntances of stop words.
* @param words	unordered map containing words and their associated word counts stored in a vector.
* @param fileName	the filename containing a list of words to trigger as stop words
*/
void removeStopWords(std::unordered_map<std::string, std::vector<int>>& words, std::string fileName)
{
	std::ifstream file(fileName.c_str());
	std::string line;
	if (!file.is_open())
	{
		std::cout << "Failed to open file: " << fileName << std::endl;
		std::exit(-1);
	}
	else
	{
		while (std::getline(file, line))
		{
			words.erase(line);
		}
	}
}


/**
* This function's purpose is to transform the contents of the given map into a sorted vector of strings.
* @param words	unordered map containing words and their associated word counts stored in a vector.
* @ return	std::vector<std::string> a vector containing sorted words.
*/
std::vector<std::string> mapToVector(std::unordered_map<std::string, std::vector<int>>& words)
{
	std::vector<std::string> vecOfWords;

	for (auto it = words.begin(); it != words.end(); ++it)
	{
		vecOfWords.emplace_back(it->first);
	}
	std::sort(vecOfWords.begin(), vecOfWords.end());

	return vecOfWords;
}

