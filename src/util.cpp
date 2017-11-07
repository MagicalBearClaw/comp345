#include <algorithm>
#include <sstream>
#include <iostream>
#include <locale>

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

int countWords(std::istream & istream){
  unsigned int count = 0;
  std::string oneWord;

  while(istream >> oneWord) {
    ++count;
  }

  return count;
}

int countWords(std::string text) {
  int ctr = 0;
  std::string delimiters = " \t\n,";
  size_t current = 0;
  size_t next = -1;
  
  do
	{
		current = next + 1;
		next = text.find_first_of(delimiters, current);
		std::string currentword = text.substr(current, next - current);
		std::transform(currentword.begin(), currentword.end(), currentword.begin(), tolower);
		if (currentword != "") {
      ++ctr;
    }
	} while (next != std::string::npos);
}

