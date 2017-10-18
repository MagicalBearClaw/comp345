#include <algorithm>
#include <sstream>
#include <iostream>

#include "../includes/util.h"

std::string crawlToDelimiter(std::istream &stream, std::string delimiters) {
  std::stringstream buffer;
  while(!stream.eof()) {
    // if the next character in the stream is not a delimiter add it to a buffer
    if (std::find(delimiters.begin(), delimiters.end(), stream.peek()) == delimiters.end()) {
      char c = stream.get();
      // check to make sure you are not at the end of file since the loop works one character in the future
      if (!stream.eof()) {
        buffer << c;
      }
    } else {
      stream.get(); // dump the delimiter
      return buffer.str();
    }
  }
  return buffer.str(); // return the remaining characters if the eof is reached
}

void drawLine(const int length) {
	for (int i = 0; i != length; ++i)
		std::cout << "*";
	std::cout << std::endl;
}


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