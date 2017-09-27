#include "document.h"

const int notFound = 0;

int Document::operator[](std::string word) {
  if (document.find(word) == document.end()) { // checks if word does not exist
    return 0;
  }
  return document[word];
}

void Document::indexWord(std::string word) {
  document[word] = (*this)[word] + 1;
}