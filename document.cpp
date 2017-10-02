#include "document.h"

const int notFound = 0;

Document::Document() 
  : punctuations("_{}[]#()<>%:;.?*+-/^&|~!=,\"'X")
 {} 

int Document::operator[](std::string word) {
  if (document.find(word) == document.end()) { // checks if word does not exist
    return 0;
  }
  return document[word];
}

void Document::indexWord(std::string word) {
  std::cout << "hello" << document[word];
  document[word] = 1;
  document[word] = (*this)[word] + 1;
}

std::ifstream & operator>>(std::ifstream &ifs, Document &doc) {
  std::string word;
  if(ifs >> word) {
    std::cout << doc.punctuations << std::endl;
    char* cursor = doc.punctuations;
    std::cout << *cursor << std::endl;
    do {
      std::cout << *cursor << std::endl;
      int pos = word.find(*cursor);
      if (pos != -1) {
        word.replace(pos, 1, "");
      }
    }while(*(++cursor) != 'X');
    std::cout << word << std::endl;
    doc.indexWord(word);
    std::cout << "hello world" << std::endl;
    // do file reading stuff for documents
  }
}
