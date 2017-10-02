// TODO complete the assignment
// https://moodle.concordia.ca/moodle/pluginfile.php/2916064/mod_resource/content/1/a1.pdf
#include "indexer.h"
 // temporary to use string as stream

int main() {
  Indexer *indexer = new Indexer();
  std::ifstream ifs("index.txt");
  assert(ifs.good() && "Invalid file name");
  while(!ifs.eof()){
    ifs >> *indexer;
  }
  std::cout << "done" << std::endl;
  // fs >> indexer;
}

Indexer::Indexer() {
  // documents = {};
}

std::ifstream & operator>>(std::ifstream &ifs, Indexer &indexer) {
  std::string fileNm;
  if(ifs >> fileNm) {
    std::cout << fileNm << std::endl;
    indexer.createDocument(fileNm);
    std::ifstream docIfs(fileNm);
    assert(docIfs.good() && "Invalid file name"); // good even if vscode complains :/
    while(!docIfs.eof()) {
      docIfs >> *indexer[fileNm];
    }
    // do file reading stuff for documents
  }
}

void indexWord(WordCtr& dict, std::string& word) {
  if (dict.find(word) == dict.end()) { // checks if word does not exist
    dict[word] = 1;
  } else {
    dict[word]++;
  }
}

void Indexer::createDocument(std::string& name) {
  documents[name] = new Document();
}

void Indexer::addWord(std::string& docName, std::string& word) {
  // add document if none exists
  if(documents.find(docName) == documents.end()) {
    createDocument(docName);
  }
  documents[docName]->indexWord(word); // move this logic into this method
}

Document* Indexer::operator[](std::string docName) {
  if (documents.find(docName) == documents.end()) {
    return nullptr;
  }
  return documents[docName];
}
