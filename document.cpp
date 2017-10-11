#include "document.h"

const int notFound = 0;

Document::Document() 
  // : punctuations("_{}[]#()<>%:;.?*+^&|~!=,\"'\0")
 {} 

Document::Document(std::string fileName): fileName(fileName) {
  // read contents into document object
}

Document::~Document() {
  delete fileContent;
}
// find a way to reuse this
int Document::operator[](std::string word) {
  if (document.find(word) == document.end()) { // checks if word does not exist
    return 0;
  }
  return document[word];
}

void Document::indexWord(std::string word) {
  document[word] = (*this)[word] + 1;
}

std::string Document::name() {
  return fileName;
}


int Document::size() {
  return fileContent->length();
}

std::string* Document::content() {
  return fileContent;
}

// std::ifstream & operator>>(std::ifstream &ifs, Document &doc) {
 
//     // do file reading stuff for documents
//   }
// }
