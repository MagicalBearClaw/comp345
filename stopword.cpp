#include "stopword.h"

StopWord::StopWord() {}

StopWord::StopWord(std::string fileName) {
  // load file
  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cout << "Missing " << fileName <<", exiting pro" <<std::endl;
    std::exit(-1);
  }
  char* stopWord;
  file.getline(stopWord, 100, ',');
  stopWords.push_back(stopWord);
}

bool StopWord::operator()(std::string word) {
  return std::find(stopWords.begin(), stopWords.end(), word) != stopWords.end();
}
