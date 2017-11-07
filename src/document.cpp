#include <sstream>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "..\includes\document.h"

//Friend function
std::ostream& operator<<(std::ostream& stream, Document& doc) {
  stream << "Document: " << doc.fileName << std::endl;
  stream << "Size: " << doc.size() << std::endl;
  stream << "Content:\n" << doc.fileContent << std::endl;
  return stream;
}

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

std::string Document::content() const {
  return fileContent;
}

std::string Document::name() const {
  return !fileName.empty() ? fileName : "unnamed document";
}

int Document::size() const {
  return _size;
}

