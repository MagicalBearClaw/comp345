#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#ifndef DOCUMENT_H
#define DOCUMENT_H

class Document {
  friend std::ifstream &  operator>>(std::ifstream &ifs, Document &doc);
public:
  int operator[](std::string word);
  void indexWord(std::string word);
private:
  std::map<std::string, int> document;
};

#endif