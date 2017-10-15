#include <map>
#include <assert.h>
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iterator>
#include <ostream>
#include <iomanip>
#include "document.h"

#ifndef INDEXER_H
#define INDEXER_H

// typedef std::map<std::string, int> WordCtr; // find better name

int main();

// void indexWord(WordCtr& dict, std::string& word);

// should keep track of largest word for styling
class Indexer {
  friend std::ifstream & operator>>(std::ifstream &ifs, Indexer &indexer);
  friend std::ostream & operator<<(std::ostream &ios, Indexer &indexer);
public:
  Indexer();
  Document* operator[](std::string docName);
  void createDocument(std::string& name);
  void addWord(std::string& docName, std::string& word);
private:
  int maxWordLength;
  std::map<std::string, Document*> documents;
  std::vector<std::string> words;
  std::vector<std::string> docNames;

};

#endif
