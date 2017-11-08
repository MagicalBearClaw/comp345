#include <sstream>
#include <algorithm>
#include <cmath>

#include "../includes/document.h"


std::ostream &operator<<(std::ostream &stream, Document &document)
{
  stream << "Document: "<< std::endl;
  stream << "Name: " << document.name() << std::endl;
  stream << "Size:(Character count of document) " << document.size() << std::endl;
  stream << "Content:\n"
         << document.content() << std::endl;
  return stream;
}
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

//Size represents different values, but method for returning size is same as sibling class.
int Document::size() const {
  return _size;
}

