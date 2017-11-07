#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <istream>
#include <vector>
#include <unordered_map>

/**
* @brief Macro to safely delete a pointer.
*/
#define SAFE_DELETE(x)		\
{							\
	if(x)                   \
	  delete x;			    \
	x = nullptr;			\
}							\

/**
 * @brief Crawls through a string to get a word before a delimiter
 * 
 * Function that takes an istream and crawls through it character by
 * character until a specified delimiter is reached at which point
 * a list of all previously hit characters is returned
 * 
 * @param stream a reference to the stream to be crawled through
 * @param delimiters a string of all delimiters to check for
 * 
 * @return the string of characters before a delimiter in the stream
 */
std::string crawlToDelimiter(std::istream &stream, std::string delimiters);

/**
* This function draws a line of asterisks based on provided length paramater.
* @param length	The length of the line you wish to draw.
*
*/
void drawLine(const int length);

/**
 * @brief This utility function returns a count of the number of words in a stream
 * 
 * returns the number of tokens seperated by white space within a stream.
 * 
 * @param istream the inputstream provided to count arguments of
 * @return int the count of words within the inputstream
 */
int countWords(std::istream & istream);
// int countWords(std::stringstream & sstream);
int countWords(std::string text);
// int countWords(std::fstream fstream);


#endif //UTIL_H