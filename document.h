#include <map>
#include <vector>
#include <string>
#include <sstream>

#ifndef DOCUMENT_H
#define DOCUMENT_H

class Document {
public:
  int operator[](std::string word);
  void indexWord(std::string word);
private:
  std::map<std::string, int> document;
};

#endif