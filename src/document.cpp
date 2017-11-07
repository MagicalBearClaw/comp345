#include <sstream>
#include <algorithm>
#include <cmath>

#include "..\includes\document.h"


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
  _size = fileContent.length();
}

Document::~Document() {}

int Document::size() const {
  return _size;
}

