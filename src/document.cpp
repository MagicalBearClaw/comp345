#include <sstream>
#include <algorithm>
#include <cmath>

#include "..\includes\document.h"


Document::Document() {} 

Document::Document(std::string fileName) {
  std::fstream file(fileName);
  std::stringstream buffer;
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << fileName << "\n";
    std::_Exit(-1);
  }
  buffer << file.rdbuf();
  _name = fileName;
  _content = buffer.str();
  _size = _content.length();
}

Document::~Document() {}

int Document::size() const {
  return _size;
}

