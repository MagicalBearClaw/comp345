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
  friend std::ostream &  operator<<(std::ostream &os, Document &doc);
public:
  Document();
  Document(std::string fileName);
  ~Document();
  int operator[](std::string word);
  void indexWord(std::string word);
  std::string name();
  int size();
  std::string* content();
private:
  // char* punctuations; // make static
  std::map<std::string, int> document; // legacy code
  std::string fileName;
  std::string* fileContent;
};

#endif
