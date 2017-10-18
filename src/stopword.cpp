#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "../includes/stopword.h"
#include "../includes/util.h"

StopWord::StopWord() {}

StopWord::StopWord(std::string fileName) {
  // load file
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cout << "Missing " << fileName <<", exiting pro" <<std::endl;
    std::exit(-1);
  }
  while (!file.eof()) {
    std::string stopWord;
    stopWord = crawlToDelimiter(file, ",\n ");
    // make sure that the string actually has content
    if(!stopWord.empty()) {
      stopWords.push_back(stopWord);
    }
  }
}

std::ostream& operator<<(std::ostream& stream, StopWord& sw) {
  for (auto i = sw.stopWords.begin(); i != sw.stopWords.end(); i++) {
    stream << *i << ", ";
  }
  stream << std::endl;

  return stream;
}

bool StopWord::operator()(std::string word) {
  return std::find(stopWords.begin(), stopWords.end(), word) != stopWords.end();
}
