#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

class StopWord {
public:
  StopWord();
  StopWord(std::string fileName);
  bool operator()(std::string word);
private:
  std::vector<std::string> stopWords;
};
