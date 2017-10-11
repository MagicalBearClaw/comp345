#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <regex>
#include <algorithm>

#ifndef DOCUMENT_H
#define DOCUMENT_H

class Document {
  // friend std::ifstream &  operator>>(std::ifstream &ifs, Document &doc);
public:
  Document();
  int operator[](std::string word);
  void indexWord(std::string word);
private:
  // char* punctuations; // make static
  std::map<std::string, int> document;
};

#endif
