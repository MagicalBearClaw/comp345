// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2916064/mod_resource/content/1/a1.pdf
#include "indexer.h"
#include <iostream>
#include <map>
#include <string>
#include <sstream> // temporary to use string as stream


int main() {
  Indexer i;
  std::string fileName = "test";
  i.createDocument(fileName);
  std::string test = "this is a test of adding test words to the dictionary"; // replace by file IO
  std::istringstream testStream(test);
  std::string word;
  while (testStream >> word) {
    i.addWord(fileName, word);
  }
  WordCtr* doc = i[fileName];
  std::cout << "test: " << (*doc)["test"] << std::endl;
  std::cout << "dictionary: " << (*doc)["dictionary"] << std::endl;
  std::cout << "this: " << (*doc)["this"] << std::endl;
  return 0;
}

Indexer::Indexer() {
  documents = {};
}

void indexWord(WordCtr& dict, std::string& word) {
  if (dict.find(word) == dict.end()) { // checks if word does not exist
    dict[word] = 1;
  } else {
    dict[word]++;
  }
}

void Indexer::createDocument(std::string& name) {
  documents[name] = {};
}

void Indexer::addWord(std::string& docName, std::string& word) {
  // add document if none exists
  if(documents.find(docName) == documents.end()) {
    createDocument(docName);
  }
  indexWord(documents[docName], word); // move this logic into this method
}

WordCtr* Indexer::operator[](std::string docName) {
  if (documents.find(docName) == documents.end()) {
    return nullptr;
  }
  return &documents[docName];
}
