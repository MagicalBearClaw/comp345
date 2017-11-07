#include "..\includes\sentence.h"

//Friend function
std::ostream& operator<<(std::ostream& stream, Sentence& sen) {
    stream << "Sentence from file: " << sen.name() << std::endl;
    stream << "Size: " << sen.size() << std::endl;
    stream << "Content:\n" << sen.content() << std::endl;
    return stream;
  }

  Sentence::Sentence() {} 

  Sentence::Sentence(std::string fileName): fileName(fileName) {
    // std::fstream file(fileName);
    // std::stringstream buffer;
    // if (!file.is_open()) {
    //   std::cout << "Failed to open file: " << fileName << std::endl;
    //   std::_Exit(-1);
    // }
    // buffer << file.rdbuf();
    // fileContent = buffer.str();
    // _size = fileContent.length();

    std::stringstream stream(strContent);
    std::string oneWord;

    unsigned int count = 0;
    while(stream >> oneWord) {++count;}
    _size = count;
  }

  Sentence::~Sentence() {}
  
  int Sentence::size() const {
    return _size;
  }

  int Sentence::getPos() const {
      return pos;
  }
  
  