#include <map>
#include <vector>
#include <string>
#include <sstream>

#ifndef INDEXER_H
#define INDEXER_H

typedef std::map<std::string, int> WordCtr; // find better name

int main();

void indexWord(WordCtr& dict, std::string& word);

class Indexer {
public:
  Indexer();
  WordCtr* operator[](std::string docName);
  void createDocument(std::string& name);
  void addWord(std::string& docName, std::string& word);
private:
  std::map<std::string, WordCtr> documents;

};

#endif
