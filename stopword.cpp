#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "util.h"
#include "stopword.h"

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

bool StopWord::operator()(std::string word) {
  return std::find(stopWords.begin(), stopWords.end(), word) != stopWords.end();
}
