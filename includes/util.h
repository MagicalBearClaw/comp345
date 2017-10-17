#include <string>
#include <istream>


#ifndef UTIL_H
#define UTIL_H

#define SAFE_DELETE(x)		\
{							\
	delete x;				\
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
#endif