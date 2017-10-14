#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>

#include "document.h"

const int notFound = 0;

Document::Document() {} 

Document::Document(std::string fileName): fileName(fileName) {
  std::fstream file(fileName);
  std::stringstream buffer;
  if (!file.is_open()) {
    std::cout << "Failed to open file: " << fileName << std::endl;
    std::_Exit(-1);
  }
  buffer << file.rdbuf();
  fileContent = buffer.str();
}

Document::~Document() {}

std::string Document::name() {
  return !fileName.empty() ? fileName : "unnamed document";
}


int Document::size() {
  return fileContent.length();
}

std::string Document::content() {
  return fileContent;
}

  // find a way to reuse this
  // int Document::operator[](std::string word) {
  //   if (document.find(word) == document.end()) { // checks if word does not exist
  //     return 0;
  //   }
  //   return document[word];
  // }